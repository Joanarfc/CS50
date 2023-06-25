def calculate_sum(card_number):
    sum = 0
    digit_position = 0
    temp = card_number

    # Loop to calculate the Luhn’s Algorithm
    while temp > 0:
        digit = temp % 10
        temp //= 10
        digit_position += 1

        # Check if the digit position is a pair. If yes, it will multiply each digit by 2
        if digit_position % 2 == 0:
            digit *= 2

            # Check if it's a two-digit number
            if (digit > 9):
                digit = (digit % 10) + 1
            sum += digit
        else:
            sum += digit

    return sum % 10 == 0


def get_first_two_digits(card_number):
    temp = card_number

    while temp > 100:
        temp //= 10

    return temp


def validate_card(card_number):
    first_two = get_first_two_digits(card_number)
    num_digits = 0
    temp = card_number

    while temp > 0:
        temp //= 10
        num_digits += 1

    if num_digits == 15 and (first_two == 34 or first_two == 37):
        print("AMEX")
    elif num_digits == 16 and (first_two > 50 and first_two < 56):
        print("MASTERCARD")
    elif (num_digits == 13 or num_digits == 16) and str(first_two)[0] == '4':
        print("VISA")
    else:
        print("INVALID\n")


# Prompt the user for a credit card number
card_number = int(input("Number: "))

# Calculate the sum of the credit card number
is_valid = calculate_sum(card_number)

# Validate the card number and print it out to the user
if is_valid:
    validate_card(card_number)
else:
    print("INVALID")