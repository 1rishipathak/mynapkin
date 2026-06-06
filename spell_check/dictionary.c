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
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 276;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Calculate hash value
    int h = hash(word);

    // List traversal and check
    node *ptr = NULL;
    for (ptr = table[h]; ptr != NULL; ptr = ptr->next)
    {

        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
        else
        {
            continue;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Create a hash function
    if (word[1] != '\0')
    {
        int f = toupper(word[0]) - 'A';
        int g = toupper(word[1]) - 'A';

        return 10 * f + g; // max possible value is 275 corresponding to zz
    }
    else
    {
        int f = toupper(word[0]) - 'A';

        return 10 * f;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Load dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Calculating hash value
        int h = hash(buffer);

        // Creating a node for word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        // Assign value of word in node
        strcpy(n->word, buffer);
        n->next = NULL;

        // Allocation node to hash table
        n->next = table[h];
        table[h] = n;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int words = 0;
    for (int i = 0; i < N; i++)
    {
        node *ptr = NULL;
        ptr = table[i];
        while (ptr != NULL)
        {
            words += 1;
            ptr = ptr->next;
        }
    }

    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // List traversal and free
    node *ptr = NULL;
    int index = 0;
    for (int i = 0; i < N; i++)
    {
        ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        index += 1;
    }

    if (index == N)
    {
        return true;
    }
    else
    {
        return false;
    }
}
