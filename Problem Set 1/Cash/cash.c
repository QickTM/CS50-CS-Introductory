#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int intCents = get_cents();

    // Calculate the number of quarters to give the customer
    int intQuarters = calculate_quarters(intCents);
    intCents = intCents - intQuarters * 25;

    // Calculate the number of dimes to give the customer
    int intDimes = calculate_dimes(intCents);
    intCents = intCents - intDimes * 10;

    // Calculate the number of nickels to give the customer
    int intNickels = calculate_nickels(intCents);
    intCents = intCents - intNickels * 5;

    // Calculate the number of pennies to give the customer
    int intPennies = calculate_pennies(intCents);
    intCents = intCents - intPennies * 1;

    // Sum coins
    int intNumCoins = intQuarters + intDimes + intNickels + intPennies;

    // Print total number of coins to give the customer
    printf("%i\n", intNumCoins);
}

int get_cents(void)
{
    // TODO
    int intCoins = 0;
    do
    {
        intCoins = get_int("Cents owed: ");
    }
    while(intCoins < 0);

    return intCoins;
}

int calculate_quarters(int intCents)
{
    //Calculate number of quaters needed
    int intQuaters = 0;
    while (intCents >=25)
    {
        intCents = intCents - 25;
        intQuaters++;
    }
    return intQuaters;
}

int calculate_dimes(int intCents)
{
    //Calculate number of dimes needed
     int intDimes = 0;
    while (intCents >= 10)
    {
        intCents = intCents - 10;
        intDimes++;
    }
    return intDimes;
}

int calculate_nickels(int intCents)
{
    //Calculate number of nickels needed
    int intNickels = 0;
    while (intCents >= 5)
    {
        intCents = intCents - 5;
        intNickels++;
    }
    return intNickels;
}

int calculate_pennies(int intCents)
{
    //Calculate number of pennies needed
    int intPennies = 0;
    while (intCents >= 1)
    {
        intCents = intCents - 1;
        intPennies++;
    }
    return intPennies;
}
