# TODO
from cs50 import get_int


def main():
    height = get_height()

    print_shape(height)


# function to get height
def get_height():
    while True:
        try:
            height = get_int("Height: ")
            if height in range(1, 9):
                return height
        except ValueError:
            pass


# function to print the pyramid
def print_shape(height):
    for i in range(height):
        print(" " * (height - 1 - i) + "#" * (i + 1) + " " * 2 + "#" * (i + 1))


main()
