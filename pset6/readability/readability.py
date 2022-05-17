from cs50 import get_string


def main():

    # Prompt user for text
    text = get_string("Text: ")

    # Count letters
    letters = count_letters(text)

    # Count words
    words = count_words(text)

    # Count sentences
    sentences = count_sentences(text)

    # Average letters per 100 words
    L = (letters * 100) / words

    # Average sentnces per 100 words
    S = (sentences * 100) / words

    # Coleman-Liau index
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Print Grade
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade {}".format(index))

# Counting 


def count_letters(sentence):
    sum_letters = 0
    for c in sentence:
        if c.isalpha():
            sum_letters += 1
    return sum_letters


def count_words(sentence):
    # Last word does not end up with space, ergo sum equals 1
    sum_words = 1
    for c in sentence:
        if c == " ":
            sum_words += 1
    return sum_words


def count_sentences(sentence):
    sum_sentences = 0
    # sentences usually end up with those signs:
    for c in sentence:
        if c == "." or c == "!" or c == "?":
            sum_sentences += 1
    return sum_sentences


if __name__ == "__main__":
    main()