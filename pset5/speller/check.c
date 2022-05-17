// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const int LENGTH = 45;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
//Number of words in dictionary
unsigned int word_count;

// Hash table
node *table[N];

//prototypes
bool load(const char *dictionary);
unsigned int hash(const char *word);
unsigned int size(void);
bool check(const char *word);
bool unload(void);


// Default dictionary
#define DICTIONARY "dictionaries/large"


int main(int argc, char *argv[])
{
    // Check for correct number of args
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

    // Determine dictionary to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;
    load(dictionary);
    //node *a = table[0]->next;
    //node *b = table[0]->next->next;
    printf("tables content:\n [0] %s\n [1] %s\n [2] %s\n", table[0]->word, table[0]->next->word, table[0]->next->next->word);
    int z = size();
    printf("the size of dictionary is: %i\n", z);
    unload();
}

//**************************************************************




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

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value = tolower(word[i]) + (hash_value << 6) + (hash_value << 16) - hash_value;
    }
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
    int index;
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
        n->next = NULL;
        //hash the word
        index = hash(word);
        //when the hash value is called for the first time
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        //when the hash value was already called
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        //keep track of word count
        word_count++;
    }
    // TODO
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    // TODO
    return true;
}
