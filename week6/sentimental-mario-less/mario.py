from cs50 import get_int


def main():
    # print function
    height = get_height()
    print_pyramid(height)


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
def print_pyramid(height):
    for i in range(height):
        print(" " * (height - 1 - i), end="")
        print("#" * (i + 1))


main()
