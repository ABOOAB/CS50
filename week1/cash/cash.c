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
    int cents = get_cents();
    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;
    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);

    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);

    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}
// this is prompt function
int get_cents(void)
{
    int cent;
    do
    {
        cent = get_int("Change owed : ");
    }
    while (cent < 0);

    return cent;
}
// this for  quarters
int calculate_quarters(int cents)
{
    int quarters;
    int cnt = 0;
    while (cents >= 100)
    {
        cents = cents - 100;
        cnt = cnt + 4;
    }
    if (cents < 50 && cents >= 25)
    {
        quarters = 1;
    }
    else if (cents < 75 && cents >= 50)
    {
        quarters = 2;
    }
    else if (cents >= 75 && cents < 100)
    {
        quarters = 3;
    }
    else
    {
        quarters = 0;
    }
    quarters = quarters + cnt;
    return quarters;
}
// calcuating dimes
int calculate_dimes(int cents)
{
    int dimes = cents / 10;
    return dimes;
}
// calculating mickels
int calculate_nickels(int cents)
{
    int nickels = cents / 5;
    return nickels;
}
// calculatin pennies
int calculate_pennies(int cents)
{
    int pennies = cents;
    return pennies;
}
