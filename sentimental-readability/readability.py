import re


def main():
    text = input('Text: ')
    # Number of letters.
    letters = len(re.findall('[a-zA-Z]', text))
    # Number of words.
    words = text.count(' ') + 1
    # Number of sentences.
    sentences = len(re.findall('[.!?]', text))

    # Average number of letters per 100 words.
    avg_letters = letters / words * 100
    # Average number of sentences per 100 words.
    avg_sentences = sentences / words * 100
    # Coleman-Liau index.
    index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8
    
    # Grade level of the text.
    grade = round(index)

    if grade > 16:
        print('Grade 16+')
    elif grade < 1:
        print('Before Grade 1')
    else:
        print(f'Grade {grade}')


if __name__ == '__main__':
    main()