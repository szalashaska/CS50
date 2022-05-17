#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

//Prompt user for number

    long nr;
    do
    {
        nr = get_long("Number: ");
    }
    while (nr <= 0);

//Determine single digits

   int digits[16];
   for (int i = 0; i < 16; i++)
    {
        long ten = pow(10, i + 1);
        digits[i] = (nr % ten - digits[i - 1]) / pow(10, i);
        printf("dig is now %i\n", digits[i]);

    }

//Multiply every secound digit and determine sum of them

    int sum_other = 0;
    int pigits[16];
    for (int j = 1; j < 16; j = j + 2)
    {
    pigits[j] = digits[j] * 2;  //multply digits
    if (pigits[j] < 10)
        {
            pigits[j] = pigits[j];  //less than 10 - sum of digits remainds the same
        }
        else
        {
            pigits[j] = pigits[j] % 10 + 1; //more than 10 - sum of digits must be modified
        }
        sum_other += pigits[j];
    }

//Add every first? digit

    int sum_rest = 0;
    for (int l = 0; l < 16; l = l + 2)
    {
        sum_rest += digits[l];
    }

//printf("%i\n", sum_rest);

//Add sums - determine control sum

    int sum_control = sum_other + sum_rest;

    printf("%i\n", sum_control);

}