import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

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
    # list for the dictioneries
    results = []
    user_id = session["user_id"]
    # Get user Stocks_symbol
    symbols = db.execute(
        "SELECT DISTINCT  stock_symbol FROM transactionss WHERE user_id = ?  ORDER BY transaction_date DESC", user_id)

    # cash
    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    cash = float(cash[0]["cash"])

    # declare grand_total
    grand_total = cash

    # Iterate over every stock_symbol
    for symboll in symbols:

        # use lookup() to get the symbol and the price
        quote = lookup(symboll["stock_symbol"])

        # Get the symbol of the current stock
        symbol = quote["symbol"]

        # Get the total shares of a specific stock_symbol
        sharess = db.execute(
            "SELECT SUM(quantity) as total_shares FROM transactionss WHERE user_id = ? AND stock_symbol = ?", session["user_id"], symbol)
        share = sharess[0]["total_shares"]

        # Get the price of the stock
        price = float(quote["price"])

        # Total cost of the shares of a specific stock
        total_cost = ((share) * (price))

        # append into the results list a dictonery of every stock
        results.append({"symbol": symbol, "price": price,
                       "shares": share, "total_cost": total_cost})

        # calaculate  all the grand_total (stocks’ total value plus cash)
        grand_total = grand_total + (price * share)

    # Return the index page and pass to it the results list of dictionres
    return render_template("index.html", results=results, cash=cash, grand_total=grand_total, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # look up the stock symbol
        symbol = request.form.get("symbol")
        result = lookup(symbol)

        # Render an apology if the input symbol is blank
        if not request.form.get("symbol"):
            return apology("input a symbol")

        # Render an apology if the symbol does not exist
        if result is None:
            return apology("invalid symbol")

        # Render an apology if the input shares is blank
        if not request.form.get("shares"):
            return apology("missing shares")

        # if not postive
        if int(request.form.get("shares")) < 0 :
            return apology("must be postive shares")

        # check if it is a whole number
        shares_str = request.form.get("shares")
        shares_float = float(shares_str)

        # check if is it string
        if shares_str.isalpha():
            return apology("Shares must be a number")

        # check if is an integer
        if not shares_float.is_integer():
           return apology("Shares must be a whole number")

        # price of the stock
        price = float(result.get("price"))

        # print price
        print(price)

        # buy the stock

        # check if the cash's user can provide the demand shares of the stock
        userrr_id = session["user_id"]

        # 1- getting the cash of the user
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", userrr_id)
        cash = user_cash[0]["cash"]
        print(cash)

        # 2- getting the demand no. of shares
        shares_number = int(request.form.get("shares"))

        # 3- check if user can purchase the no. of demand
        total_require = price * int(shares_number)
        print(total_require)

        # Get the current timestamp
        current_timestamp = datetime.utcnow()

        if (cash < total_require):
            return apology("not enough money")
        else:
            # inserting into the transaction table the result of transaction process
            db.execute("INSERT INTO transactionss (user_id, stock_symbol, quantity, price, transaction_date, type) VALUES (?, ?, ?, ?, ?, ?)",
                       userrr_id, symbol, shares_number, price, current_timestamp,'buy')

            # update the cash amount of the user
            new_cash = cash - (total_require)

            # updating the cash number of the user
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, userrr_id)

            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactionss = db.execute("SELECT * FROM transactionss WHERE user_id = ?",session["user_id"])

    return render_template("/history.html",transactionss=transactionss, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember whisch user has logged in
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

        # look up the stock symbol
        symbol = request.form.get("symbol")

        # handle
        if not request.form.get("symbol"):
            return apology("blank", 400)

        result = lookup(symbol)

        if result is not None:
            # getting the price and convert it into usd_form
            price = result.get("price")
            usd_format = usd(price)
            return render_template("quoted.html", quotes=result, usd_format=usd_format)
        else:
            return apology("this is stock is unavilable", 400)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure  confirmation password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 400)

        # Ensure confirmation password equal to password
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 400)

        # Ensure that user name is not taken
        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        if len(rows) == 1:
            return apology("username is already taken", 400)

        # username  & hash the password
        username = request.form.get("username")
        hash_password = generate_password_hash(request.form.get("password"))

        # Insert the data user in the user's database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_password)

        # Retrieve the id of the inserted user
        user_idd = db.execute("SELECT id FROM users WHERE username = ?", username)[0]['id']

        # Remember which user has logged in
        session["user_id"] = user_idd

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    """Sell shares of stock"""
    # getting all of the stocks
    stocks = db.execute("SELECT stock_symbol FROM transactionss WHERE user_id=?", session["user_id"])

    if request.method == "POST":
        # if empty blank
        if not request.form.get("symbol"):
            return apology("Enter a symbol", 400)

        # check for the symbol exsist
        symbol = request.form.get("symbol").upper()
        rows = db.execute("SELECT stock_symbol FROM transactionss WHERE stock_symbol = ?",symbol)
        if len(rows) == 0:
            return apology("you didn't have this stocks")

        # Check for postive number of shares
        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("you must enter postive number")

        # check if the user own this shares
        results = db.execute("SELECT SUM(quantity) as total FROM transactionss WHERE stock_symbol = ? ", symbol)
        if results:
            quantity = results[0]["total"]
        else:
            return apology("No matching transactions found")

        if quantity < shares:
            return apology("you don't have the no. of shares")

        # sell
        # 1- update the number of shares of that symbol
        # quantity = quantity - shares
        # trans_id = db.excute("SELECT transaction_id FROM transctionss WHERE ")
        # db.execute("UPDATE transactionss SET quantity = ? WHERE user_id = ? AND stock_symbol = ? AND transaction_id = ?", quantity, session["user_id"],symbol)

        # 2- update the user cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        price = db.execute("SELECT price FROM transactionss WHERE stock_symbol = ?", symbol)[0]["price"]
        cash += price * shares
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        # Get the current timestamp
        current_timestamp = datetime.utcnow()

        # inserting into the transaction table the result of transaction process
        db.execute("INSERT INTO transactionss (user_id, stock_symbol, quantity, price, transaction_date, type) VALUES (?, ?, ?, ?, ?, ?)",
                    session["user_id"], symbol, -shares, price, current_timestamp,'sell')

        # insert into db the type
        type = "sell"
        db.execute("INSERT INTO transactionss (type) VALUES (?)",type)

        # return to home page
        return redirect("/")
    else:
        return render_template("sell.html", stocks=stocks)

