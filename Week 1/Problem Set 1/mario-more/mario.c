#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt the user about the height of the pyramids
    do
    {
        height = get_int("Height:");
    } while (height<1 || height>8);

    // Loop to print out the pyramids
    for (int i = 1; i <= height; i++)
    {
        // Print out left pyramid
        for (int j = 1; j <= height - i; j++)
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        // Print out middle between pyramids, which is only 1 space
        printf("  ");

        // Print out right pyramid
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}