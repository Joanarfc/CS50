// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool isuppercase = false;
    bool islowercase = false;
    bool isnumber = false;
    bool issymbol = false;

    int length = strlen(password);

    for (int i = 0; i < length; i++)
    {
        if (isdigit(password[i]))
        {
            isnumber = true;
        }
        else if (islower(password[i]))
        {
            islowercase = true;
        }
        else if (isupper(password[i]))
        {
            isuppercase = true;
        }
        else if (!isalnum(password[i]))
        {
            issymbol = true;
        }
    }

    return isuppercase && islowercase && isnumber && issymbol;;
}
