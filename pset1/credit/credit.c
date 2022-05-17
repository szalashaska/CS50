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
//Determine what are the digits
    int a_1 = nr % 10;
    int a_2 = (nr % 100 - a_1) / 1e1;
    int a_3 = (nr % 1000 - a_2) / 1e2;
    int a_4 = (nr % 10000 - a_3) / 1e3;
    int a_5 = (nr % 100000 - a_4) / 1e4;
    int a_6 = (nr % 1000000 - a_5) / 1e5;
    int a_7 = (nr % 10000000 - a_6) / 1e6;
    int a_8 = (nr % 100000000 - a_7) / 1e7;
    int a_9 = (nr % 1000000000 - a_8) / 1e8;
    int a_10 = (nr % 10000000000 - a_9) / 1e9;
    int a_11 = (nr % 100000000000 - a_10) / 1e10;
    int a_12 = (nr % 1000000000000 - a_11) / 1e11;
    int a_13 = (nr % 10000000000000 - a_12) / 1e12;
    int a_14 = (nr % 100000000000000 - a_13) / 1e13;
    int a_15 = (nr % 1000000000000000 - a_14) / 1e14;
    int a_16 = (nr % 10000000000000000 - a_15) / 1e15;

//Multiply every other digit

    int b_2 = a_2 * 2;
    int b_4 = a_4 * 2;
    int b_6 = a_6 * 2;
    int b_8 = a_8 * 2;
    int b_10 = a_10 * 2;
    int b_12 = a_12 * 2;
    int b_14 = a_14 * 2;
    int b_16 = a_16 * 2;
//Determine the individual digits and add them
    int c_2;
    if (b_2 < 10)
    {
        c_2 = b_2;
    }
    else
    {
        c_2 = b_2 % 10 + 1;
    }

    int c_4;
    if (b_4 < 10)
    {
        c_4 = b_4;
    }
    else
    {
        c_4 = b_4 % 10 + 1;
    }
    int c_6;
    if (b_6 < 10)
    {
        c_6 = b_6;
    }
    else
    {
        c_6 = b_6 % 10 + 1;
    }
    int c_8;
    if (b_8 < 10)
    {
        c_8 = b_8;
    }
    else
    {
        c_8 = b_8 % 10 + 1;
    }
    int c_10;
    if (b_10 < 10)
    {
        c_10 = b_10;
    }
    else
    {
        c_10 = b_10 % 10 + 1;
    }
    int c_12;
    if (b_12 < 10)
    {
        c_12 = b_12;
    }
    else
    {
        c_12 = b_12 % 10 + 1;
    }
    int c_14;
    if (b_14 < 10)
    {
        c_14 = b_14;
    }
    else
    {
        c_14 = b_14 % 10 + 1;
    }
    int c_16;
    if (b_16 < 10)
    {
        c_16 = b_16;
    }
    else
    {
        c_16 = b_16 % 10 + 1;
    }
//Sum of all previously determined digits
    int sum1 = c_2 + c_4 + c_6 + c_8 + c_10 + c_12 + c_14 + c_16;
//Adding sum1 and digits, that were left over
    int sum2 = sum1 + a_1 + a_3 + a_5 + a_7 + a_9 + a_11 + a_13 + a_15;
//Print card name / validity
    if (nr >= 1e12 && nr < 1e13) //13 digits
    {
        if (a_13 == 4)
        {
            if (sum2 % 10 == 0) //sumcheck
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (nr >= 1e14 && nr < 1e15) //15 digits
    {
        if (a_15 == 3)
        {
            if (a_14 == 4 || a_14 == 7)
            {
                if (sum2 % 10 == 0) //sumcheck
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (nr >= 1e15 && nr < 1e16) //16 digits
    {
        if (a_16 == 4)
        {
            if (sum2 % 10 == 0) //sumcheck
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (a_16 == 5)
        {
            if (a_15 > 0 && a_15 <= 5)
            {
                if (sum2 % 10 == 0) //sumcheck
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else //all the other
    {
        printf("INVALID\n");
    }
}