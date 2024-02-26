import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd, validate_account

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
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    symbols = db.execute(
        "SELECT DISTINCT symbol from transactions where user_id = ? GROUP BY symbol HAVING SUM(shares) > 0",
        user_id,
    )

    # insert into the stock table
    for symbol in symbols:
        stock = lookup(symbol["symbol"])
        db.execute(
            "INSERT INTO stock (symbol, price) VALUES (?, ?)",
            stock["symbol"],
            stock["price"],
        )

    # Prepare the transactions database
    transactions = db.execute(
        """
                        SELECT transactions.symbol AS symbol,
                            SUM(transactions.shares) AS shares,
                            stock.price AS price,
                            SUM(transactions.shares * stock.price) AS total
                        FROM transactions
                        JOIN stock ON transactions.symbol = stock.symbol
                        WHERE transactions.user_id = ?
                        GROUP BY transactions.symbol, stock.price
                    """,
        user_id,
    )

    # format the transactions
    for transaction in transactions:
        transaction["price"] = usd(transaction["price"])
        transaction["total"] = usd(transaction["total"])

    # Prepare the total value
    totaly = db.execute(
        """
                    SELECT SUM(transactions.shares * stock.price) + users.cash AS totaly
                    FROM transactions
                    JOIN stock ON transactions.symbol = stock.symbol
                    JOIN users ON transactions.user_id = users.id
                    WHERE users.id = ?;
                 """,
        user_id,
    )
    total = usd(totaly[0]["totaly"]) if totaly[0]["totaly"] is not None else usd(10000)

    cash = usd(cash[0]["cash"])
    # delete the stock database after usage
    db.execute("DELETE FROM stock")

    return render_template(
        "index.html", transactions=transactions, cash=cash, total=total
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # handel get request
    if request.method == "GET":
        return render_template("buy.html")

    # handel post request
    else:
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")  # string type
        stock = lookup(symbol)  # dict type
        user_id = session["user_id"]  # int type
        cash_db = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id
        )  # list of dict type
        cash = cash_db[0]["cash"]  # float type

        # Ensure symbol submit
        if not symbol:
            return apology("Missing symbol")
        # Ensure shares submit
        if not shares:
            return apology("Missing shares")

        try:
            if int(shares) < 0 or not shares.isdigit():
                raise ValueError("Shares should be a positive integer.")
            shares = int(shares)
        except (ValueError, TypeError):
            return apology("Invalid shares value. Please enter a positive integer.")

        # Ensure symbol is exist
        if not stock:
            return apology("Symbol not exist.")
        # Ensure shares is an integer
        try:
            shares < 0 and not str(shares).isdigit()
        except ValueError:
            return apology("Shares should be a positive integer.")

        # Ensure that user have a sufficient amount of cash
        transaction_val = shares * stock["price"]
        if cash < transaction_val:
            return apology("Not enough cash")

        # Complete the transaciton and Update the user cash
        new_cash = cash - transaction_val
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        db.execute(
            "INSERT INTO transactions \
                  (user_id, symbol, shares, price, date) \
                  VALUES (?, ?, ?, ?, ?)",
            user_id,
            symbol,
            shares,
            usd(stock["price"]),
            datetime.datetime.now(),
        )

        # flash a message
        flash("Bought!")
        # Back to main page
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute(
        """
                              SELECT symbol, shares, price, date
                              FROM transactions
                              WHERE user_id = ?""",
        user_id,
    )
    return render_template("history.html", transactions=transactions)


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
        session["username"] = request.form.get("username")

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

    # handel GET request
    if request.method == "GET":
        return render_template("quote.html")

    # hanel POST request
    else:
        # Get the date from the form
        symbol = request.form.get("symbol")

        # Ensure the symbol was submitted
        if not symbol:
            return apology("Symbol can not be empty.")

        stock = lookup(symbol)
        if not stock:
            return apology("This symbol is not exist.")

        return render_template(
            "quoted.html", price=usd(stock["price"]), symbol=stock["symbol"]
        )


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # handel GET request
    if request.method == "GET":
        return render_template("register.html")
    # handel post request
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # handel blank username request
        if not username:
            return apology("must provide username")

        # handel password and connfirmation password
        if not password or not confirmation:
            return apology("Please enter your password and/or confirmation")

        # Ensure username match
        if password != confirmation:
            return apology(" password and confirmation is not match")

        # insert the new user into database
        hash = generate_password_hash(password)

        try:
            new_user = db.execute(
                "INSERT INTO users(username, hash) VALUES (?, ?)", username, hash
            )

        except:
            return apology("Username has been taken")

        # start session and back to main page
        session["user_id"] = new_user
        flash("Registered!")
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    # Handel the GET request
    if request.method == "GET":
        symbols = db.execute(
            "SELECT DISTINCT symbol from transactions where user_id = ? GROUP BY symbol HAVING SUM(shares) > 0",
            user_id,
        )
        return render_template("sell.html", symbols=symbols)

    # Handel the POST request
    else:
        symbol = request.form.get("symbol")
        shares_db = db.execute(
            "SELECT SUM(shares) AS shares FROM transactions WHERE user_id = ? AND symbol = ?",
            user_id,
            symbol,
        )[0]["shares"]
        shares = int(request.form.get("shares"))
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        price = lookup(symbol)["price"]

        # Ensure stock selction
        if not symbol:
            return apology("Missing symblo")
        # Ensure that it's a positive integer
        if shares < 0:
            return apology("Shares should be a positive integer")

        # Ensure enough shares
        if shares > shares_db:
            return apology("too many shares")

        # Update completion
        # Update cash
        new_cash = cash + (price * shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        # insert the transaction
        db.execute(
            "INSERT INTO transactions(user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
            user_id,
            symbol,
            shares * -1,
            usd(price),
            datetime.datetime.now(),
        )

        # flash the message
        flash("Sold!")
        # Redirect to the home page
        return redirect("/")


@app.route("/settings", methods=["GET"])
@login_required
def settings():
    return render_template("settings.html")


@app.route("/change_password", methods=["POST"])
def change_password():

    oldpassword = request.form.get("oldpassword")
    newpassword = request.form.get("newpassword")
    confirmation = request.form.get("confirmation")
    user_id = session["user_id"]

    # Check if the password is not correct
    if not check(user_id, oldpassword):
        return redirect(url_for("change_password"))

    # Check if the confirmaiont is not correct
    if newpassword != confirmation:
        flash("confirmation Not correct")
        return redirect(url_for("change_password"))

    # Update the password
    newpassword = generate_password_hash(newpassword)
    db.execute("UPDATE users SET hash = ? WHERE id = ?", newpassword, user_id)
    flash("Your password has been changed!")
    return render_template("settings.html")


@app.route("/change_username", methods=["POST"])
def change_username():
    # Gather the required data
    old_username = request.form.get("oldusername")
    new_username = request.form.get("newusername")
    password = request.form.get("confirmation")
    user_id = session["user_id"]

    # Check username
    if not check(user_id, password, old_username):
        return redirect(url_for("change_username"))

    # Check uniqueness of the password
    try:
        db.execute("UPDATE users SET username = ? WHERE id = ?", new_username, user_id)
    except:
        flash("This username has beed taken before!")
        return render_template("/settings.html")

    # update username
    db.execute("UPDATE users SET username = ? WHERE id = ?", new_username, user_id)
    flash(f"Your username has been changed to {new_username} sucsessfully!")
    return render_template("/settings.html")


@app.route("/add_cash", methods=["POST"])
def add_cash():

    # gather required data
    account = request.form.get("account_number")
    password = request.form.get("confirmation")
    amount = round(float(request.form.get("amount")), 2)
    user_id = session["user_id"]

    # Check the password
    if not check(user_id, password):
        return redirect(url_for("add_cash"))

    # Ensure the account information
    if not validate_account(account):
        flash("Faild to add the new amount, Invalid account!")
        return render_template("/settings.html")

    # Update cash amount
    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", amount, user_id)
    flash("The new cash amount has been added!")
    return redirect("/")


def check(user_id, password, username=None):
    user_data = db.execute("SELECT username, hash FROM users WHERE id = ?", user_id)
    if username:
        if username.lower() != user_data[0]["username"].lower():
            flash("Your username is not correct")
            return False

    if not check_password_hash(user_data[0]["hash"], password):
        flash("Password Not correct")
        return False

    return True
