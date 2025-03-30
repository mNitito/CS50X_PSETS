// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// node_counter
int node_counter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = 0;
    // Hash the word to obtain its hash value
    index = hash(word);
    // Search the hash table at the location specified by the word’s hash value
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            // Return true if the word is found
            return true;
            break;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    // Return false if no word is found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // hashing by total sum of the ascii values
    int hash_size = N;
    int total_hash_value = 0;
    int i = 0;
    while (word[i] != '\0')
    {
        total_hash_value += tolower((int) word[i]);
        i++;
    }
    total_hash_value %= hash_size;

    return total_hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    char buffer[LENGTH + 1];
    int index;

    // open the dictonery file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("couldn't open the dictionary\n");
        return 1;
    }

    while (fscanf(file, "%s", buffer) != EOF)
    {

        // allocating a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return 2;
        }
        strcpy(n->word, buffer);
        index = hash(n->word);
        if (table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        node_counter++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return node_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = 0; i < 25; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        table[i] = NULL;
    }

    return true;
}
