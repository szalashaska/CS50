#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

bool character(string input); //checks for characters in key

bool correct_key(string input); //check for correctness of key

int main(int argc, string argv[])
{

//If we become right input
    if (argc == 2 && strlen(argv[1]) == 26 && character(argv[1]) && correct_key(argv[1]))
    {

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
                    cipher = tolower(argv[1][plaintext[i] - 'a']);
                    printf("%c", cipher);
                }
                else //Upper characters
                {
                    cipher = toupper(argv[1][plaintext[i] - 'A']);
                    printf("%c", cipher);
                }
            }
            else //Non alphabetic characters
            {
                cipher = plaintext[i];
                printf("%c", cipher);
            }
        }

//magic

        printf("\n");
        return 0;

    }
//If we become wrong input: 0 or more than 1 arguments
    else if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
//If input key is not correct
    else
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

}

bool character(string input)
{
    bool k = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (isalpha(input[i])) //check every substring if it is alphabetic
        {
            k = true;
        }
        else
        {
            k = false; //if not return false
            return k;
        }
    }
    return k;
}

bool correct_key(string input)
{
    bool k = 0;
    int count = 0;
    int count_2 = 0;
    for (int l = 0; l <= 'z' - 'a'; l++) //count sum of all ASCII letters
    {
        count = count + l;
    }

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (isupper(input[i]))
        {
            count_2 = count_2 + (input[i] - 'A'); //count sum of key letters -if upper
        }
        else
        {
            count_2 = count_2 + (input[i] - 'a');//count sum of key letters - if lower
        }
    }
    if (count == count_2) //compere sums - if diffrent letters were multiple times
    {
        k = true;
    }
    else
    {
        k = false;
    }
    return k;
}