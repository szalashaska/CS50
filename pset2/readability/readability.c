#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Initiating counting fuction - letters, words, sentences
int count_letters(string sentence);
int count_words(string sentence);
int count_sentences(string sentence);

int main(void)
{

//Prompt for text
    string text = get_string("Text: ");

//Count letters
    float letters = count_letters(text);
    //printf("%f letter(s)\n", letters);

//Count words
    float words = count_words(text);
    //printf("%f word(s)\n", words);

//Count sentences
    float sentences = count_sentences(text);
    //printf("%f sentence(s)\n", sentences);

//Avarge letters per 100 words
    float L = (letters * 100) / words;
    //printf("L = %.3f\n", L);

//Avarge sentences per 100 words
    float S = (sentences * 100) / words;
    //printf("S = %.3f\n", S);

//Coleman-Liau index
    float index = round(0.0588 * L - 0.296 * S - 15.8);

//Print Grade

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }

}
// Counting fuctions

int count_letters(string sentence) //count letters
{
    int sum_letters = 0;
    for (int i = 0, n = strlen(sentence); i < n; i++)
    {
        if (isupper(sentence[i]))
        {
            sum_letters++;
        }
        else if (islower(sentence[i]))
        {
            sum_letters++;
        }
    }
    return sum_letters;
}

int count_words(string sentence) //count words
{
    int sum_words = 1; //counting the last word (the last have no space)
    for (int i = 0, n = strlen(sentence); i < n; i++)
    {
        if (sentence[i] == ' ')
        {
            sum_words++;
        }
    }
    return sum_words;
}

int count_sentences(string sentence) //count sentences
{
    int sum_sentences = 0;
    for (int i = 0, n = strlen(sentence); i < n; i++)
    {
        if (sentence[i] == '.' || sentence[i] == '?' || sentence[i] == '!')
        {
            sum_sentences++;
        }
    }
    return sum_sentences;
}