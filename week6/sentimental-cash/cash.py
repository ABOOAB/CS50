# import important moduels

from cs50 import get_float


def main():
    cents = get_cents()

    quarters = calculate_quarters(cents)
    cents = round(cents - (0.25 * quarters), 2)

    dimes = calculate_dimes(cents)
    cents = round(cents - (0.10 * dimes), 2)

    nickels = calculate_nickels(cents)
    cents = round(cents - (0.05 * nickels), 2)

    pennies = calculate_pennies(cents)

    print(int(quarters + dimes + nickels + pennies))


def get_cents():
    while True:
        cents = get_float("Change owed : ")
        if cents > 0:
            return cents


def calculate_quarters(cents):
    if cents < 1:
        return int(cents / 0.25)
    else:
        quarters = 0
        while cents > 0.99:
            cents -= 1
            quarters += 4
        return quarters + int(cents / 0.25)


def calculate_dimes(cents):
    return int(cents / 0.10)


def calculate_nickels(cents):
    return int(cents / 0.05)


def calculate_pennies(cents):
    pennies = 0
    while cents:
        pennies += 1
        cents -= 0.01
    return pennies


main()
