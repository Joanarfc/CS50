#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompts the name of the user
    string name = get_string("What's your name: ");

    // Prints out a saludation to the user
    printf("hello, %s\n", name);
}