#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    char c = get_char("Input: ");
    if (isdigit(c))
    {
        printf("Your input is a digit.\n");
    }
    else
    {
        printf("Your input is not a digit.\n");
    }
}