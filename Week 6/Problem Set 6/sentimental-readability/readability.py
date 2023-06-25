def count_letters(text):
    countletters = 0

    # Iterate over each character in the text
    for char in text:
        if char.isalpha():
            countletters += 1

    return countletters


def count_words(text):
    # Split the text into individual words using whitespace as the delimiter
    countwords = text.split()

    return len(countwords)


def count_sentences(text):
    # Iterate over each character in the text
    countsentences = 0

    for char in text:
        # Check if the character is a sentence-ending punctuation mark
        if char in ['!', '.', '?']:
            countsentences += 1

    return countsentences


def print_grade(text):
    words = 100

    # Calculate the average number of letters per 100 words
    average_letters = (count_letters(text) / count_words(text)) * words

    # Calculate the average number of sentences per 100 words
    average_sentences = (count_sentences(text) / count_words(text)) * words

    # Calculate the Coleman-Liau index using the average letter and sentence counts
    index = round((0.0588 * average_letters) - (0.296 * average_sentences) - 15.8)

    # Determine the corresponding grade level based on the index
    if index >= 16:
        print("Grade 16+\n")
    elif index < 1:
        print("Before Grade 1\n")
    else:
        print(f"Grade {index}")


input_text = input("Text: ")

print_grade(input_text)