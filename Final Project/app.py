import os
import io
import matplotlib.pyplot as plt
import logging
import pandas as pd
import numpy as np
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, send_file
from flask_session import Session
from flask_wtf import CSRFProtect
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# for security
# app.secret_key = '100000'  # You should use a strong secret key
# csrf = CSRFProtect(app)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///user.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Render the index page with user info"""
    user_id = session.get("user_id")
    
    if user_id:
        user = db.execute("SELECT * FROM table_users WHERE id = ?", user_id)
        if user:
            user_name = user[0]['full_name']
            logged_in = True
        else:
            user_name = "Guest"  # Fallback name if user is not found
            logged_in = False
    else:
        user_name = "Guest"  # Default name if no user is logged in
        logged_in = False

    return render_template("index.html", user_name=user_name, logged_in=logged_in)


@app.route("/sign-in", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return ("error 403")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return ("error 403")

        # Query database for username
        rows = db.execute(
            "SELECT * FROM table_users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return ("user not exsist 403")

        # Remember whisch user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sign-in.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/sign-up", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Ensure fullname was submitted
        if not request.form.get("fullname"):
            return apology("must provide fullname", 400)
        
         # Ensure fullname was submitted
        if not request.form.get("email"):
            return apology("must provide email", 400)

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)


        # Ensure that user name is not taken
        # Query database for username
        rows = db.execute(
            "SELECT * FROM table_users WHERE username = ?", request.form.get("username")
        )
        if len(rows) == 1:
            return apology("username is already taken", 400)

        # username  & hash the password
        username = request.form.get("username")
        hash_password = generate_password_hash(request.form.get("password"))
        email = request.form.get("email")
        full_name = request.form.get("fullname")

        # Insert the data user in the user's database
        db.execute("INSERT INTO table_users (username, hash, email, full_name) VALUES (?, ?, ?, ?)", username, hash_password, email, full_name)

        # Retrieve the id of the inserted user
        result = db.execute("SELECT id FROM table_users WHERE username = ?", username)
        user_idd = result[0]['id']

        # Remember which user has logged in
        session["user_id"] = user_idd

        return redirect("/")

    else:
        return render_template("sign-up.html")


@app.route('/General')
@login_required
def general():
    return render_template('General.html')

@app.route('/Animals_trivia')
@login_required
def animals():
    return render_template('Animals_trivia.html')

@app.route('/Gamming')
@login_required
def gameing():
    return render_template('Gamming.html')


@app.route('/update_score', methods=["POST"])
@login_required
def update_score():
    # Get the score change from the request (can be positive or negative)
    data = request.get_json()
    score_change = data.get("score_change", 0)
    print(score_change)

    user_id = session["user_id"]

    # Retrieve the current score
    user = db.execute("SELECT score FROM table_users WHERE id = ?", user_id)
    current_score = user[0]['score'] if user else 0

    # Calculate the new score
    new_score = current_score + score_change

    # update the recent score
    db.execute("UPDATE table_users SET score = ? WHERE id = ?", new_score, user_id)

    # Insert the new score into user_scores
    db.execute("INSERT INTO user_scores (user_id, score) VALUES (?, ?)", user_id, new_score)

    return {"success": True}

@app.route('/score')
@login_required
def score_page():
    # Retrieve user score from the database
    user_id = session["user_id"]
    user = db.execute("SELECT score FROM table_users WHERE id = ?", user_id)

    # Get the score
    score = user[0]['score'] if user else 0

    # Create the performance chart
    return render_template('Score.html', score=score)

@app.route('/performance_chart')
@login_required
def performance_chart():
    # Retrieve user scores from the database
    user_id = session["user_id"]
    scores = db.execute("SELECT score FROM user_scores WHERE user_id = ? ORDER BY id ASC", user_id)
    print(scores)

    # Get the scores
    scores = [score['score'] for score in scores]
    print(scores)
    print(len(scores))

    # Set the logging level for matplotlib to WARNING or higher
    logging.getLogger('matplotlib').setLevel(logging.WARNING)

    # Set PIL's logger to a higher level (e.g., ERROR) to suppress debug messages
    logging.getLogger("PIL").setLevel(logging.ERROR)

    # Generate a plot
    plt.figure(figsize=(10, 6))
    x = range(1, len(scores) + 1)
    plt.plot(x, scores, marker='o', linestyle='-')

    

    plt.title('User Performance')
    plt.xlabel('Attempts')
    plt.ylabel('Score')
    plt.ylim(min(scores) - 1, max(scores) + 1)  # Set y-axis limits to whole numbers
    plt.xticks(ticks=np.arange(0, len(scores), step=20), labels=[f'{i}' for i in range(0, len(scores), 20)])    
    plt.yticks(range(min(scores), max(scores) + 20, 20))  # Show whole numbers on y-axis
    plt.grid(True)

    # Save the plot to a BytesIO object
    img = io.BytesIO()
    plt.savefig(img, format='png')
    img.seek(0)  # Move to the beginning of the BytesIO object

    return send_file(img, mimetype='image/png')