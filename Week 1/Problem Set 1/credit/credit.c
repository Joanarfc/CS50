#include <cs50.h>
#include <stdio.h>

bool calculate_sum(long card_number);
int get_first_two_digits(long card_number);
void validate_card(long card_number);

int main(void)
{
    long card_number;

    // Prompt the user for a credit card number
    card_number = get_long("Number: ");

    // Calculate the sum of the credit card number
    bool is_valid = calculate_sum(card_number);

    // Validate the card number and print it out to the user
    if (is_valid)
    {
        validate_card(card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool calculate_sum(long card_number)
{
    int sum = 0, digit, digit_position = 0;
    long temp = card_number;

    // Loop to calculate the Luhn’s Algorithm
    while (temp > 0)
    {
        digit = temp % 10;
        temp /= 10;
        digit_position++;

        // Check if the digit position is a pair. If yes, it will multiply each digit by 2
        if (digit_position % 2 == 0)
        {
            digit *= 2;

            // Check if it's a two-digit number
            if (digit > 9)
            {
                digit = (digit % 10) + 1;
            }
            sum += digit;
        }
        else
        {
            sum += digit;
        }
    }
    return sum % 10 == 0;
}

int get_first_two_digits(long card_number)
{
    long temp = card_number;

    while (temp > 100)
    {
        temp /= 10;
    }

    return temp;
}

void validate_card(long card_number)
{
    int first_two = get_first_two_digits(card_number);
    int num_digits = 0;
    long temp = card_number;

    while (temp > 0)
    {
        temp /= 10;
        num_digits++;
    }

    if (num_digits == 15 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if (num_digits == 16 && (first_two > 50 && first_two < 56))
    {
        printf("MASTERCARD\n");
    }
    else if ((num_digits == 13 || num_digits == 16) && first_two / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}