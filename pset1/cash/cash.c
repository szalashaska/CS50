#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

//Prompt user for amount of change
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change <= 0);

//Use the largest coins possible, keep track of coins used
    int coins = 0;
    int cents = round(change * 100);
    while (cents > 0)
    {
        if (cents >= 25)
//count 25 cents
        {
            cents = cents - 25;
        }
        else if (cents < 25 && cents >= 10)
//count 10 cents
        {
            cents = cents - 10;
        }
        else if (cents < 10 && cents >= 5)
//count 5 cents
        {
            cents = cents - 5;
        }
        else if (cents < 5 && cents >= 1)
//count 1 cent
        {
            cents = cents - 1;
        }

        coins++;
    }
//Print the number of coins
    printf("%i\n", coins);

}