from cs50 import get_string

def main():
    # prompt string from the user
    text = input("Text: ")

    # calculate number of letters
    letters = count_letters(text)

    # calculate number of words
    words = count_words(text)

    # calculate number of sentences
    sentences = count_sentences(text)

    # calculate the grade
    index = calc_grade(letters, words, sentences)

    # print the grade
    grade(index)


def calc_grade(letters, words, sentences):
    L = letters / words * 100
    S = sentences / words * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    return round(index)


def grade(index):
    if index >= 16:
        print("Grade 16+")

    elif 1 <= index < 16:
        print(f"Grade {index}")
    else:
        print("Before Grade 1")


def count_letters(text):
    cnt = 0
    for i in text:
        if i.isalpha():
            cnt += 1
    return cnt


def count_words(text):
    cnt = 0
    for i in text:
        if i == " ":
            cnt += 1
    return cnt + 1


def count_sentences(text):
    cnt = 0
    for i in text:
        if i in [".", "!", "?"]:
            cnt += 1
    return cnt


if __name__ == "__main__":
    main()
