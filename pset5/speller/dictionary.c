// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//Prime number of my choice
const unsigned int N = 11939;

//Number of words in dictionary
unsigned int word_count;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = 0;
    //calculate hash value for word
    index = hash(word);
    //check if word have assigned table index
    if (table[index] == NULL)
    {
        return false;
    }
    //serch for word in hash table
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }
    return false;
}

/*
 * Hashes word to a number
 * Source of hash function: http://www.cse.yorku.ca/~oz/hash.html
 * @param const char* word - word we want return a hash value for.
 * @return unsigned int hash_value - returns the hashed value.
 */
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value = tolower(word[i]) + (hash_value << 6) + (hash_value << 16) - hash_value;
    }
    //hash value uses modulo N to fit into size of hash table
    return (hash_value % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open dictionary
    FILE *input = fopen(dictionary, "r");
    //check for error
    if (input == NULL)
    {
        return false;
    }
    //buffer array for reading and hash index variable
    char word[LENGTH + 1];
    unsigned int index;
    //variable to count words in dictionary
    word_count = 0;
    //read words from dictionary
    while (fscanf(input, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        //check for error
        if (n == NULL)
        {
            return false;
        }
        //copy word from buffer to new node
        strcpy(n->word, word);
        //no need for that: n->next = NULL;
        //hash the word
        index = hash(word);
        n->next = table[index];
        table[index] = n;

        //keep track of word count
        word_count++;
    }
    //close the dictionary
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // returns number of words in dictionary (counted in load() function)
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //iterate over every position in the hash table
    for (int i = 0; i < N; i++)
    {
        //free every linked list in the hash table
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
