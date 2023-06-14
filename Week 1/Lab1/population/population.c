#include <cs50.h>
#include <stdio.h>

int calculate_years(int start, int end, int years);

int main(void)
{
    int start_size, end_size;
    int years = 0;

    // TODO: Prompt for start size
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    years = calculate_years(start_size, end_size, years);

    // TODO: Print number of years
    printf("Years: %i\n", years);
}

int calculate_years(int start, int end, int years)
{
    while (start < end)
    {
        start += (start / 3) - (start / 4);
        years++;
    }
    return years;
}