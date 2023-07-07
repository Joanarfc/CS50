import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Validate if the input month is a valid month
        if not month.isdigit() or int(month) < 1 or int(month) > 12:
            return redirect("/")
        
        # Validate if the input day is a valid month
        if not day.isdigit() or int(day) < 1 or int(day) > 31:
            return redirect("/")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?,?,?)", name, month, day)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

@app.route("/delete", methods=["POST"])
def deletebirthday():

        # Delete birthday record
        id = request.form.get("id")
        if id:
            db.execute("DELETE FROM birthdays WHERE id = ?", id)

        return redirect("/")

@app.route("/update", methods=["POST"])
def update_birthday():
    # Retrieve the updated values from the form
    id = request.form.get("id")
    name = request.form.get("name")
    month = request.form.get("month")
    day = request.form.get("day")

    if id:
        # Update the birthday record in the database
        db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?", name, month, day, id)

    return redirect("/")

@app.route("/edit", methods=["POST"])
def edit_birthday():
    # Retrieve the ID of the birthday to be edited
    id = request.form.get("id")

    if id:
        # Retrieve the existing birthday record from the database
        birthday = db.execute("SELECT * FROM birthdays WHERE id = ?", id)
        
        return render_template("edit.html", birthday=birthday[0])
