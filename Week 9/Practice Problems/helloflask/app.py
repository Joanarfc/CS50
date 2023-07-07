from flask import Flask, render_template, request

app = Flask(__name__)

COLORS = {
    "Harvard Crimson": "red",
    "Yale Blue": "blue"
}

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html", color_dict=COLORS)
    else:
        print("Form submitted!")
        color_selected = request.form.get("color")

        # Input validation
        if color_selected in COLORS.values():
            return render_template("color.html", color=color_selected)
        else:
            error_message = "Invalid color selection. Please choose a color from the options provided."
            return render_template("failure.html", color_dict=COLORS, error_message=error_message)