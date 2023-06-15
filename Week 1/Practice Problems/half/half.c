// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include "../../libs/CS50/cs50.h"
#include <stdio.h>

float half(float bill, float tax, float tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    float tip_percent = get_float("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, float tip)
{
    tax = tax / 100;
    tip = tip / 100;

    bill = (float) bill + ((float) tax * bill);

    return ( (float) bill + ((float) tip * (float) bill)) / (float) 2;
}