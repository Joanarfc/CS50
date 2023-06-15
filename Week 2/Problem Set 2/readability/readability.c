#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void print_grade(string text);

int main(void)
{
    string input = get_string("Text: ");

    print_grade(input);
}

int count_letters(string text)
{
    int countletters = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        text[i] = tolower(text[i]);

        if (!ispunct(text[i]) && !isdigit(text[i]) && isalpha(text[i]) && (islower(text[i]) || isupper(text[i])))
        {
            countletters ++;
        }
    }
    return countletters;
}

int count_words(string text)
{
    int countwords = 1;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (isspace(text[i]))
        {
            countwords ++;
        }
    }
    return countwords;
}

int count_sentences(string text)
{
    int countsentences = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            countsentences ++;
        }
    }
    return countsentences;
}

void print_grade(string text)
{
    const int words = 100;

    float average_letters = (((float) count_letters(text) / (float) count_words(text)) * words);
    float average_sentences = (((float) count_sentences(text) / (float) count_words(text)) * words);

    int index = round((0.0588 * average_letters) - (0.296 * average_sentences) - 15.8);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}