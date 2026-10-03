// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table.
const unsigned int N = 1496267;

int dictionary_size = 0; // Number of words in the dictionary.

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_value = hash(word);
    node* n = table[hash_value];

    // Traverse the linked list to search the word.
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }

        n = n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        c = tolower(c);
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    
    hash %= N;

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary.
    FILE* dictionary_file = fopen(dictionary, "r");

    if (dictionary_file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    // Read dictionary word by word.
    while (fscanf(dictionary_file, "%s", word) != EOF)
    {
        // Allocate a new node for each word.
        node* n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        // Compute hash value of the word.
        int hash_value = hash(word);
        // Insert node in the hash table.
        n->next = table[hash_value];
        table[hash_value] = n;
        dictionary_size++;
    }

    fclose(dictionary_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node* n = table[i];

        while (n != NULL)
        {
            node* temp = n;
            n = n->next;
            free(temp);
        }

        if (i == N - 1 && n == NULL)
        {
            return true;
        }
    }

    return false;
}