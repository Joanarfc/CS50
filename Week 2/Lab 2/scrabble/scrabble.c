#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int length = strlen(word);
    int score = 0;
    int index;

    for (int i = 0; i < length; i++)
    {
        // Convert the character to lowercase
        word[i] = tolower(word[i]);

        // Checks if the character is a letter and not a punctuation
        if (!ispunct(word[i]) && isalpha(word[i]))
        {
            if (tolower(word[i]))
            {
                // IF the character is lowercase, we want to subtract the ASCII value of 'a' (97)
                index = word[i] - 'a';
                score += POINTS[index];
            }
            if (toupper(word[i]))
            {
                // IF the character is lowercase, we want to subtract the ASCII value of 'A' (65)
                index = word[i] - 'A';
                score += POINTS[index];
            }
            score += POINTS[index];
        }
        // If the character is punctuation, we add 0 score
        else if (ispunct(word[i]))
        {
            score += 0 ;
        }
        // Else, if the character is neither punctuation or a letter, we also add 0 score
        else
        {
            score += 0 ;
        }
    }
    return score;
}