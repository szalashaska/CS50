#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Initiating checking function
bool digit_check(string input);

int main(int argc, string argv[])
{

//If we become right input
    if (argc == 2 && digit_check(argv[1]) && atoi(argv[1]) > 0)
    {
//Convert string into an integer, trunction k, so it is < 26
        int k = (atoi(argv[1])) % 26;
//Prompt for plaintext
        string plaintext = get_string("plaintext: ");
//Print ciphertext
        printf("ciphertext: ");

        char cipher = 0;
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            if (isalpha(plaintext[i])) //check for alphabetic
            {
                if (islower(plaintext[i])) //check for lower characters
                {
                    cipher = 'a' + (k + plaintext[i] - 'a') % 26;
                    printf("%c", cipher);
                }
                else //Upper characters
                {
                    cipher = 'A' + (k + plaintext[i] - 'A') % 26;
                    printf("%c", cipher);
                }

            }
            else //Non alphabetic characters
            {
                cipher = plaintext[i];
                printf("%c", cipher);
            }
        }

        printf("\n");
        return 0;

    }
//If we become wrong input: 0 or more than 1 arguments
    else if (argc != 2)
    {
        printf("None / wrong command-line argument\n");
        return 1;
    }
//If input is not decimal
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

//Definition of checking function
bool digit_check(string input)
{
    bool k;
    for (int i = 0, n = strlen(input); i < n; i++) //checking every character if it is a digit
    {
        if (isdigit(input[i]))
        {
            k = true;
        }
        else
        {
            k = false;
            return k;
        }
    }
    return k;
}