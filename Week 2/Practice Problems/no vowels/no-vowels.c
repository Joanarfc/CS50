// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string input);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
    else
    {
        string input = argv[1];
        replace(input);
        printf("%s\n", input);
    }
}

string replace(string input)
{
    int length = strlen(input);

    for (int i = 0; i < length; i++)
    {
        switch (input[i])
        {
            case 'a':
                input[i] = '6';
                break;

            case 'e':
                input[i] = '3';
                break;

            case 'i':
                input[i] = '1';
                break;

            case 'o':
                input[i] = '0';
                break;

            case 'u':
                break;

            default:
                break;
        }
    }
    return input;
}