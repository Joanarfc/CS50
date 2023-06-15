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

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Variable for counting words
int countWords = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashNum = hash(word);

    // Create a cursor variable
    node *cursor = table[hashNum];

    // Iterate until the end of the Linked List
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *dictionaryfile = fopen(dictionary, "r");

    // Check if return value from the dictionary file is NULL
    if (dictionaryfile == NULL)
    {
        return false;
    }

    // Read strings from file one at a time
    char str[LENGTH + 1];
    while (fscanf(dictionaryfile, "%s", str) != EOF)
    {
        // Create a new node for each word
        // Use malloc to allocate memor
        node *temp = malloc(sizeof(node));

        // Check if return value is NULL
        if (temp == NULL)
        {
            return false;
        }

        // Copy word into node using strcpy
        strcpy(temp->word, str);

        // Hash word to obtain a hash value
        // Use the hash function
        int hashNum = hash(str);

        // Check if head is pointing to NULL
        if (table[hashNum] == NULL)
        {
            // If head is pointing to NULL, then point temp to NULL
            temp->next = NULL;
        }
        else
        {
            // Otherwise, point temp to the 1st node of the Linked List
            // Insert node into hash table at that location
            temp->next = table[hashNum];
        }

        // Point the head to temp
        table[hashNum] = temp;

        // Increment the countWords variable
        countWords++;
    }

    // Close the file
    fclose(dictionaryfile);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return countWords;
}

void freeNodes(node *n)
{
    if (n == NULL)
    {
        return;
    }
    freeNodes(n->next);
    free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate over each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        // Recursively free the memory for each node in the Linked List
        freeNodes(table[i]);
    }

    return true;
}