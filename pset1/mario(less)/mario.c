#include <cs50.h>
#include <stdio.h>

int main(void)
{
//Choose height

    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

//Create a piramid

    int n = height;
//rows
    for (int i = 0; i < n; i++)
    {
//column spacebar
        for (int k = 1; k < (n - i); k++)
        {
            printf(" ");
        }
//columns #
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}