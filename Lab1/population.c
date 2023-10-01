#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int intStartSize, intEndSize;

    // TODO: Prompt for start size
    do
    {
        intStartSize = get_int("Enter start size: ");
    }
    while (intStartSize < 9);

    // TODO: Prompt for end size
    do
    {
        intEndSize = get_int("Enter end size: ");
    }
    while (intEndSize < intStartSize);

    // TODO: Calculate number of years until we reach threshold
    int intYears = 0;
    do
    {
        intStartSize = intStartSize + intStartSize / 3 - intStartSize /4;
        intYears++;
    }
    while(intStartSize < intEndSize);

    // TODO: Print number of years
    printf("Years: %i\n", intYears);
}
