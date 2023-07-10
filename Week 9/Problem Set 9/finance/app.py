import datetime
import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    user_transactions_db = db.execute(
        "SELECT symbol, SUM(shares) as shares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    user_cash = user_cash_db[0]["cash"]

    # Calculate the total value of all stocks
    total_stocks_value = sum(row["shares"] * row["price"] for row in user_transactions_db)

    # Calculate the total amount (cash + stocks value)
    total_amount = user_cash + total_stocks_value

    return render_template("index.html", transactions=user_transactions_db, cash=user_cash, total=total_amount)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Retrieve form data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Input validations
        if not symbol:
            return apology("Must provide a symbol")

        # Use the lookup function to get stock information
        stock = lookup(symbol)

        if stock == None:
            return apology("Symbol does not exist")
        
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Please enter a valid number of shares")
        
        shares = int(shares)

        # Calculate the total transaction amount
        transaction_amount = stock["price"] * shares

        # Get the user_id
        user_id = session["user_id"]

        # Retrieve user's current cash balance
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        # Check if user can afford the purchase
        if transaction_amount > user_cash:
            return apology("Insufficient money to complete the purchase")

        # Update user's cash balance
        update_user_cash = user_cash - transaction_amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_user_cash, session["user_id"])

        # Add the transaction record in the transactions table
        date = datetime.datetime.now()
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
            session["user_id"], stock["symbol"], shares, stock["price"], date
        )

        # Flash message
        flash("Shares bought successfully!", "success")

        # Redirect user to home page
        return redirect("/")

    else:
        # Get the symbol from the URL query parameters
        symbol = request.args.get("symbol")

        # Render the buy.html template and pass the symbol
        return render_template("buy.html", symbol=symbol)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions_db = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions_db)


@app.route("/add-cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Allow user to add cash to their account"""
    if request.method == "POST":
        new_cash = float(request.form.get("cash"))

        if not new_cash or new_cash < 0:
            return apology("You must provide a value")
        
        user_id = session["user_id"]

        # Retrieve user's current cash balance
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        update_user_cash = user_cash + new_cash

        # Update user's cash balance in the users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_user_cash, user_id)

        return redirect("/")
    
    else:
        return render_template("addcash.html")
   

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Retrieve stock symbol entered by the user
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Must provide a symbol")

        # Use the lookup function to get stock information
        stock = lookup(symbol)

        if stock == None:
            return apology("Symbol does not exist")
        
        # Render the quoted.html template with the stock information
        return render_template("quoted.html", quoted=stock)

    else:
        # Render the quote.html template
        return render_template("quote.html")

    
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Validate form inputs
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username")
        if not password:
            return apology("must provide password")
        if not confirmation:
            return apology("must provide confirmation")
        if password != confirmation:
            return apology("passwords do not match")
        
        # Check if username already exists
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) > 0:
            return apology("Username already taken")

        # Hash the password
        hashed_password = generate_password_hash(password)

        # Insert the new user into database
        new_user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password)

        # Store the ID of the newly registered user in the session for automatic login
        session["user_id"] = new_user

        # Redirect the user to the home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Retrieve form data
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Input validations
        if not symbol:
            return apology("Must provide a symbol")

        # Use the lookup function to get stock information
        stock = lookup(symbol)

        if stock == None:
            return apology("Symbol does not exist")
        
        if not shares or shares <= 0:
            return apology("Please enter a valid number of shares")

        # Get the user_id
        user_id = session["user_id"]

        # Retrieve user's current number of shares
        user_shares_db = db.execute(
            "SELECT SUM(shares) as shares FROM transactions WHERE user_id = ? AND symbol = ?", user_id, symbol)
        user_shares = user_shares_db[0]["shares"]

        # Check if user can afford the sell
        if user_shares is None or shares > user_shares:
            return apology("You don't have that many shares of this stock")

        # Retrieve user's current cash balance
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        # Calculate the total sale amount
        transaction_amount = stock["price"] * shares

        # Update user's shares and cash balance
        update_user_shares = user_shares - shares
        update_user_cash = user_cash + transaction_amount

        # Add the sell record in the transactions table
        date = datetime.datetime.now()
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
            user_id, symbol, -shares, stock["price"], date
        )

        # Update user's cash balance in the users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_user_cash, user_id)

        # Flash message
        flash("Shares sold successfully!", "success")

        # Redirect user to home page
        return redirect("/")
    
    else:
        # Get the symbol from the URL query parameters
        symbol = request.args.get("symbol")

        # Retrieve the user's symbols to populate the select menu in the form
        user_id = session["user_id"]
        user_symbols_db = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
        user_symbols = [row["symbol"] for row in user_symbols_db]
        return render_template("sell.html", selected_symbol=symbol, user_symbols=user_symbols)