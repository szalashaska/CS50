import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Append db to variables
    stocks = db.execute("SELECT stock_name, quantity FROM stocks WHERE user_id = ? GROUP BY stock_name", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]["cash"]

    # Check actual price, append to variable
    total = 0
    for stock in stocks:
        company = lookup(stock["stock_name"])
        stock["long_name"] = company["name"]
        stock["price"] = company["price"]
        total += float(stock["price"]) * int(stock["quantity"])

    # Calculate the sum of stock value and users cash
    total = total + float(cash)

    return render_template("index.html", stocks=stocks, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Use float on share, in case wrong input is passed, later it will be detected
        try:
            shares = float(request.form.get("shares"))
        except:
            return apology("incorrect shares")

        # Ensure company symbol is correct
        company = lookup(symbol)

        if not symbol or company is None:
            return apology("incorrect symbol")

        # Ensure shares are correct
        if not shares or (shares % 1) != 0 or shares <= 0:
            return apology("incorrect shares amount")
        else:
            shares = int(shares)

        # Check users cash amount
        row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = row[0]["cash"]
        transaction = shares * company["price"]

        if cash < transaction:
            return apology("not enough cash")

        # Update accounts cash amount
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", transaction, session["user_id"])

        # Create record of transaction
        db.execute("INSERT INTO history (stock_name, quantity, price, timestamp, user_id) VALUES (?, ?, ?, CURRENT_TIMESTAMP, ?)",
                   company["symbol"], shares, company["price"], session['user_id'])

        # Check if stocks are alredy bought, append if yes, create new entry if not
        stock_list = db.execute("SELECT * FROM stocks WHERE stock_name = ? AND user_id = ?", company["symbol"], session["user_id"])

        if len(stock_list) == 1:
            db.execute("UPDATE stocks SET quantity = quantity + ? WHERE stock_name = ? AND user_id = ?",
                       shares, company["symbol"], session["user_id"])
        else:
            db.execute("INSERT INTO stocks (stock_name, quantity, user_id) VALUES (?, ?, ?)",
                       company["symbol"], shares, session["user_id"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/buy/search")
@login_required
def search():
    # Users input, keyup
    q = request.args.get("q")

    # When we recive an input
    if q:
        company = lookup(q)
    else:
    # When there is no input
        company = []

    # Return list of recorded companies
    return jsonify(company)

@app.route("/quote/search")
@login_required
def search_quote():
    # Users input, keyup
    q = request.args.get("q")

    # if input is delivered
    if q:
        company = []
        # Range defined with ASCII letters, from a to z

        if not lookup(q) is None:
                company.append(lookup(q))

        for i in range(ord("a"), ord("z") + 1):

            # Adding first letter, from a to z to users input
            first = q + chr(i)

            # If company symbol is valid, append shortcut
            if not lookup(first) is None:
                company.append(lookup(first))

            """
            #Adding second letter, from a to z to users input and previous letter
            for k in range(ord("a"), ord("z") + 1):
                second = first + chr(k)

                #If company symbol is valid, append shortcut
                if not lookup(second) is None:
                    company.append(second)
            """

    # When there is no input
    else:
        company = []

    # List of recorded companies
    return jsonify(company)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE user_id = ? ORDER BY timestamp", session["user_id"])

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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
        symbol = request.form.get("symbol")

        # Ensure symbol exists
        company = lookup(symbol)

        if not symbol or company is None:
            return apology("symbol does not exists")

        # Print looked up data
        else:
            return render_template("quoted.html", company=company)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username")

        # Ensure password was submitted (correctly)
        elif not password:
            return apology("must provide password")
        elif password != confirmation:
            return apology("passwords does not match")

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username does not already exists
        if len(rows):
            return apology("username already taken")

        # Hash password and insert the user into db
        hash_password = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash_password)

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT stock_name, quantity FROM stocks WHERE user_id = ?", session["user_id"])

    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Use float on shares to filter out wrong input
        try:
            shares = float(request.form.get("shares"))
        except:
            return apology("incorrect shares")

        # Ensure company name and shares quantity was correctly provided
        if not symbol:
            return apology("incorrect symbol")

        # Check with db if users owns stock
        check_symbol = db.execute("SELECT * FROM stocks WHERE stock_name = ? AND user_id = ?", symbol, session["user_id"])
        if len(check_symbol) != 1:
            return apology("user does not own this stock")

        if not shares or (shares % 1) != 0 or shares <= 0:
            return apology("incorrect shares amount")
        else:
            shares = int(shares)

        # Check with db if amount of stock is correct
        shares_quantity = db.execute("SELECT quantity FROM stocks WHERE stock_name = ? AND user_id = ?", symbol, session["user_id"])
        shares_quantity = shares_quantity[0]["quantity"]
        if shares > shares_quantity:
            return apology("user does not own that many shares")

        # Current value of stock
        company = lookup(symbol)
        transaction = shares * company["price"]

        # Update accounts cash amount
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", transaction, session["user_id"])

        # Create record of transaction in the history db
        db.execute("INSERT INTO history (stock_name, quantity, price, timestamp, user_id) VALUES (?, ?, ?, CURRENT_TIMESTAMP, ?)",
                   company["symbol"], (-1) * shares, company["price"], session['user_id'])

        # Update stocks quantity, delete entry if no stocks left
        if shares_quantity - shares == 0:
            db.execute("DELETE FROM stocks WHERE stock_name = ? AND user_id = ?", company["symbol"], session["user_id"])
        else:
            db.execute("UPDATE stocks SET quantity = quantity - ? WHERE stock_name = ? AND user_id = ?",
                       shares, company["symbol"], session["user_id"])

        return redirect("/")

    else:
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
