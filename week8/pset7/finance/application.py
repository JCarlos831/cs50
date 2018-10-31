import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # stock = lookup(request.form.get("symbol"))
    # shares = request.form.get("shares")

    portfolio = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])

    for p in portfolio:
        symbol = p["symbol"]
        shares = p["shares"]
        price = p["current_price"]
        share_value = p["share_value"]

    totalValueOfAllShares = db.execute(
        "SELECT SUM(share_value) FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])
    totalValueOfAllShares = totalValueOfAllShares[0]['SUM(share_value)']
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    cash = cash[0]["cash"]

    try:
        totalValueOfAllShares = float(totalValueOfAllShares)
    except:
        totalValueOfAllShares = 0

    try:
        grandTotal = cash + totalValueOfAllShares
    except:
        grandTotal = 0

    return render_template("index.html", portfolio=portfolio, cash=cash, totalValueOfAllShares=totalValueOfAllShares, grandTotal=grandTotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Ensure quote field is not blank
        if not request.form.get("symbol"):
            return apology("Missing stock symbol!")

        # Lookup stock
        stock = lookup(request.form.get("symbol"))

        # If stock could not be found
        if not stock:
            return apology("Please enter a valid stock")

        # Get number of shares from buy form
        shares = request.form.get("shares")

        # Ensure shares are not blank
        if not shares:
            return apology("Shares must not be blank")

        # # Make shares a int
        # shares = int(shares)

        try:
            shares = int(shares)
        except:
            return apology("You didn't enter a number! Shame on you.")

        # Ensure shares can not be zero or negative
        if shares <= 0:
            return apology("Shares must not be Zero or Negative")

        # get the user's cash from the database
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        cash = cash[0]["cash"]

        totalPurchase = stock["price"] * shares

        # check to see if user has enough cash for the stock purchase
        if cash < totalPurchase:
            return apology("Not enough funds for this purchase")

        # update transactions
        db.execute("INSERT INTO transactions (symbol, name, shares, price, total, user_id) VALUES (:symbol, :name, :shares, :price, :total, :user_id)",
                   symbol=stock["symbol"], name=stock["name"], shares=shares, price=stock["price"], total=totalPurchase, user_id=session["user_id"])

        # update the user's cash
        db.execute("UPDATE users SET cash = cash - :totalPurchase WHERE id = :id",
                   id=session["user_id"], totalPurchase=totalPurchase)

        user_shares = db.execute("SELECT shares FROM portfolio WHERE user_id = :user_id AND symbol = :symbol",
                                 user_id=session["user_id"], symbol=stock["symbol"])

        # if the user does not have any shares of a particular symbol add new stock row to portfolio
        if not user_shares:
            db.execute("INSERT INTO portfolio (symbol, name, shares, current_price, share_value, user_id) VALUES (:symbol, :name, :shares, :current_price, :share_value, :user_id)",
                       symbol=stock["symbol"], name=stock["name"], shares=shares, current_price=stock["price"], share_value=totalPurchase, user_id=session["user_id"])

        # update number of shares for the particular symbol for the particular user
        else:
            totalShares = user_shares[0]["shares"] + shares
            share_value = totalShares * stock["price"]
            db.execute("UPDATE portfolio SET shares = :shares, current_price = :current_price, share_value = :share_value WHERE user_id = :user_id AND symbol = :symbol",
                       shares=totalShares, current_price=stock["price"], share_value=share_value, user_id=session["user_id"], symbol=stock["symbol"])

        return redirect(url_for('index'))

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])

    return render_template("history.html", history=history)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    """Get stock quote."""

    if request.method == "POST":

        # Ensure quote field is not blank
        if not request.form.get("symbol"):
            return apology("Missing stock symbol!")

        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Symbol is invalid")

        return render_template("quoteDisplay.html", stock=stock)

    else:
        return render_template("quote.html")


@app.route("/quoteDisplay")
@login_required
def quoteDisplay():
    """Display stock quote"""
    return render_template("quoteDisplay.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Ensure form fields are not blank
        if not request.form.get("username"):
            return apology("Missing username!")
        elif not request.form.get("password"):
            return apology("Missing password!")
        elif not request.form.get("confirmation"):
            return apology("Missing password confirmation!")

        # Ensure passwords match
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("Passwords do not match!")
        else:
            hash = generate_password_hash(request.form.get("password"))

        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                            username=request.form.get("username"), hash=hash)

        if not result:
            return apology("User already exists")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Ensure quote field is not blank
        if not request.form.get("symbol"):
            return apology("Missing stock symbol!")

        # Lookup stock
        stock = lookup(request.form.get("symbol"))

        # If stock could not be found
        if not stock:
            return apology("Please enter a valid stock")

        # Get number of shares from sell form
        shares = request.form.get("shares")

        # Ensure shares are not blank
        if not shares:
            return apology("Shares must not be blank")

        # Make shares an int
        shares = int(shares)

        # Ensure shares can not be zero or negative
        if shares <= 0:
            return apology("Shares must not be Zero or Negative")

        # select the symbol shares of that user
        user_shares = db.execute("SELECT shares FROM portfolio WHERE user_id = :user_id AND symbol=:symbol",
                                 user_id=session["user_id"], symbol=stock["symbol"])

        # check if enough shares to sell
        if not user_shares or int(user_shares[0]["shares"]) < shares:
            return apology("Not enough shares")

        totalSale = stock["price"] * shares

        # Update transactions
        db.execute("INSERT INTO transactions (symbol, name, shares, price, total, user_id) VALUES (:symbol, :name, :shares, :price, :total, :user_id)",
                   symbol=stock["symbol"], name=stock["name"], shares=shares, price=stock["price"], total=totalSale, user_id=session["user_id"])

        # update the user's cash
        db.execute("UPDATE users SET cash = cash + :totalSale WHERE id = :id", id=session["user_id"], totalSale=totalSale)

        # decrement the shares count
        shares_total = user_shares[0]["shares"] - shares
        share_value = shares_total * stock["price"]

        # if after decrement is zero, delete shares from portfolio
        if shares_total == 0:
            db.execute("DELETE FROM portfolio WHERE user_id=:user_id AND symbol=:symbol",
                       user_id=session["user_id"], symbol=stock["symbol"])
        # otherwise, update portfolio shares count
        else:
            db.execute("UPDATE portfolio SET shares=:shares, current_price = :current_price, share_value = :share_value WHERE user_id=:user_id AND symbol=:symbol",
                       shares=shares_total, current_price=stock["price"], share_value=share_value, user_id=session["user_id"], symbol=stock["symbol"])

        # return to index
        return redirect(url_for("index"))

    else:
        stocks = db.execute("SELECT symbol FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])
        return render_template("sell.html", stocks=stocks)


@app.route("/funds", methods=["GET", "POST"])
@login_required
def funds():
    """Add funds to user's cash"""
    if request.method == "POST":
        if not request.form.get("funds"):
            return apology("You must enter an amount")

        moreCash = request.form.get("funds")
        print(moreCash)

        db.execute("UPDATE users SET cash = cash + :moreCash WHERE id = :id", id=session["user_id"], moreCash=moreCash)

        return redirect(url_for("index"))

    else:
        return render_template("funds.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)