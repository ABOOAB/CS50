// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;
int dictionarySize = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash the word //
    unsigned int index = hash(word);
    // access linked list at that index in the hash table //
    node *cursor = table[index];

    // traverse linked list, looking for the word //
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
    unsigned int index;
    if (strlen(word) == 1)
    {
        index = (toupper((word[0])) - 'A') * (26 * 26);
    }
    else if (strlen(word) == 2)
    {
        index = (toupper((word[0])) - 'A') * (26 * 26) + (toupper((word[1])) - 'A') * (26);
    }
    else
    {
        index = (toupper((word[0])) - 'A') * (26 * 26) + (toupper((word[1])) - 'A') * (26) + (toupper((word[2])) - 'A') * 1;
    }
    return index;
}
//========================NEW HASH FUNCTION =======================//
// unsigned int *hash(const char *word)
// {
//     unsigned int *arr = malloc(sizeof(int) * 3);
//     unsigned int *index = arr;
//     if (strlen(word) == 1)
//     {
//         arr[0] = (toupper((word[0])) - 'A');
//         arr[1] = 0;
//         arr[2] = 0;
//     }
//     else if (strlen(word) == 2)
//     {
//         arr[0] = (toupper((word[0])) - 'A');
//         arr[1] = (toupper((word[1])) - 'A');
//         arr[2] = 0;
//     }
//     else
//     {
//         arr[0] = (toupper((word[0])) - 'A');
//         arr[1] = (toupper((word[1])) - 'A');
//         arr[2] = (toupper((word[2])) - 'A');
//     }

//     return index;
// }
//=================================================================//

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file//
    FILE *file = fopen(dictionary, "rb");
    if (file == NULL)
    {
        printf("CAN'T OPEN THE DICTIONARY \n");
        return false;
    }
    for (int i = 0; i < N; i++)

        table[i] = NULL;

    // reading strings from file//
    char word[LENGTH];
    while (fscanf(file, "%s", word) != EOF)
    {
        // create a new node //

        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            printf("CAN'T ALLOCATE MEMORY \n ");
            unload();
            fclose(file);
            return false;
        }
        // copy string into new node //
        strcpy(new->word, word);

        // hash the word //
        unsigned int index = hash(word);

        // insert node into hash table //
        if (table[index] == NULL)
        {
            new->next = NULL;
        }
        else
        {
            new->next = table[index];
        }
        table[index] = new;
        //
        dictionarySize++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    return dictionarySize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *p = NULL;
    for (int i = 0; i < N; i++)
    {
        p = table[i];
        while (p != NULL)
        {
            p = p->next;
            free(table[i]);
            table[i] = p;
        }
    }

    return true;
}
