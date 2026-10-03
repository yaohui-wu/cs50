#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Average number of letters per 100 words.
    double avg_letters = letters * 100.0 / words;
    // Average number of sentences per 100 words.
    double avg_sentences = sentences * 100.0 / words;
    // Coleman-Liau index.
    double index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;
    // Grade level of the text.
    int grade = round(index);
    
    if (grade > 16)
    {
        printf("Grade 16+");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %d", grade);
    }
    printf("\n");
    
    return 0;
}

int count_letters(string text)
{
    int sum = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if (isalpha(text[i]))
        {
            sum++;
        }
        i++;
    }

    return sum;
}

int count_words(string text)
{
    int sum = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if (isspace(text[i]))
        {
            sum++;
        }
        i++;
    }
    sum++;

    return sum;
}

int count_sentences(string text)
{
    int sum = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sum++;
        }
        i++;
    }

    return sum;
}