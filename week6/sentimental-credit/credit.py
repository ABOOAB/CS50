# importing

import cs50
import re


def main():
    # 1- get card number
    num = get_card()
    # get Luhn's sum
    Lu_sum = check_sum(num)

    # check validity and print type
    print("INVALID") if Lu_sum[-1] != "0" else check(num)


def get_card():
    while True:
        try:
            num = cs50.get_string("Number : ")
            # check by re.
            if re.search(r"^[0-9]+$", num):
                return num
            else:
                raise ValueError

        except:
            pass


def check(num):
    if len(num) == 15 and num[0:2] in ["34", "37"]:
        print("AMEX")

    elif len(num) == 16 and num[0:2] in ["51", "52", "53", "54", "55"]:
        print("MASTERCARD")

    elif len(num) == 16 and num[0] == "4":
        print("VISA")

    elif len(num) == 13 and num[0] == "4":
        print("VISA")
    else:
        print("INVALID")

    ...


# this function calculate nummber of digit and Luhn sum
def check_sum(num):
    # get sum of every other digit, starting with the number’s second-to-last digit * 2
    Lsum = 0
    for i in num[-2::-2]:
        if len(str(int(i) * 2)) == 1:
            Lsum += int(i) * 2
        else:
            Lsum += 1 + int(str(int(i) * 2)[-1])

    # add those products’ digits

    # add that sum (13) to the sum of the digits that weren’t multiplied by 2 (starting from the end)
    for i in num[-1::-2]:
        Lsum += int(i)

    return str(Lsum)

    ...


if __name__ == "__main__":
    main()
