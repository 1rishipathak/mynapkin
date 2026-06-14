import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
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
    stocks = db.execute("SELECT DISTINCT stock FROM orders WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash_balance = usd(cash[0]["cash"])
    i = -1
    holdings = []
    l_value = 0
    for stock in stocks:
        i += 1
        holdings.append({})
        holdings[i]["stock"] = stock["stock"]
        holdings[i]["qty"] = (db.execute("SELECT SUM (qty) FROM orders WHERE stock = ? AND user_id = ?",
                              stock["stock"], session["user_id"]))[0]["SUM (qty)"]
        n_stock = lookup(stock["stock"])
        l_value = float(holdings[i]["qty"]) * float(n_stock["price"])
        holdings[i]["price"] = usd(float(n_stock["price"]))
        holdings[i]["value"] = usd(l_value)
    valuation = usd(cash[0]["cash"] + l_value)
    return render_template("index.html", holdings=holdings, placeholder=valuation, cash=cash_balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    now = datetime.now()
    if request.method == "GET":
        return render_template("buy.html")
    if request.method == "POST":
        sym = request.form.get("symbol")
        try:
            qty = int(request.form.get("shares"))
        except ValueError:
            return apology("Please enter a positive integer", 400)

        if not sym:
            return apology("Please enter the stock", 400)
        if not qty or int(qty) < 1:
            return apology("Please enter a positive quantity of shares", 400)

        stock = lookup(sym)

        if stock == None:
            return apology("Stock does not exist", 400)
        else:
            value = stock["price"] * int(qty)
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

            if float(cash[0]["cash"]) < value:
                return apology("Sorry! You do not have enough cash.", 400)
            else:
                cash_new = float(cash[0]["cash"]) - value
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_new, session["user_id"])
                db.execute("INSERT INTO orders (user_id, type, stock, qty, price, datetime) VALUES (?, ?, ?, ?, ?, ?)",
                           session["user_id"], "BUY", stock["symbol"], qty, stock["price"], now)
                return redirect("/")


@app.route("/history")
@login_required
def history():
    price = 0
    rows = db.execute(
        "SELECT stock, qty, type, price, datetime FROM orders WHERE user_id = ?", session["user_id"])
    for row in rows:
        stock = lookup(row["stock"])
        price = float(stock["price"])
        t_value = price * float(row["qty"])
    return render_template("history.html", rows=rows, price=usd(price))


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
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        sym = request.form.get("symbol")
        stock = lookup(sym)
        if stock == None:
            return apology("Stock does not exist", 400)
        else:
            return render_template("quoted.html", name=stock["name"], price=usd(stock["price"]), symbol=stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username or username == "":
            return apology("Please choose a username.", 400)
        if not password or password == "":
            return apology("Please choose a password.", 400)
        if not confirmation or confirmation == "":
            return apology("Please re-enter your password.", 400)
        if password != confirmation:
            return apology("Password and Confirmation do not match", 400)

        else:
            hash = generate_password_hash(password, method='scrypt', salt_length=16)
            try:
                db.execute("INSERT INTO users (username, hash, cash) VALUES (?, ?, ?)",
                           username, hash, 10000)
                return redirect("/")
            except ValueError:
                return apology("Username already exists", 400)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    now = datetime.now()
    stocks = db.execute("SELECT DISTINCT stock FROM orders WHERE user_id = ?", session["user_id"])
    if request.method == "GET":
        return render_template("sell.html", stocks=stocks)
    if request.method == "POST":
        sym = request.form.get("symbol")
        qty_max = db.execute("SELECT SUM (qty) FROM orders WHERE stock = ? AND user_id = ?",
                             sym, session["user_id"])[0]["SUM (qty)"]
        qty = request.form.get("shares")

        if not sym:
            return apology("Please enter a stock.", 400)
        if not qty or int(qty) < 1 or qty == "" or int(qty) > qty_max:
            return apology("Please enter a positive quantity of shares.", 400)

        stock = lookup(sym)

        if stock == None:
            return apology("Stock does not exist", 400)
        else:
            value = stock["price"] * int(qty)
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

            cash_new = float(cash[0]["cash"]) + value
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_new, session["user_id"])
            db.execute("INSERT INTO orders (user_id, type, stock, qty, price, datetime) VALUES (?, ?, ?, ?, ?, ?)",
                       session["user_id"], "SELL", stock["symbol"], int("-" + qty), stock["price"], now)
            return redirect("/")


@app.route("/changepass")
@login_required
def changepass():
    if request.method == "GET":
        return render_template("changepass.html")
    else:
        password = request.form.get("pass")
        if not password:
            return apology("Please choose a new password", 400)
        hash = generate_password_hash(password, method='scrypt', salt_length=16)
        db.execute("UPDATE users SET hash = ? WHERE user_id = ?", hash, session["user_id"])
        return redirect("/")
