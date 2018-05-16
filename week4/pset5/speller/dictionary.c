// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// define max size of hashtable. this number is a constant.
// tried several numbers, this seemed to be the fastest.
#define HASHTABLE_SIZE 66500

// define a node structure
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *hashtable[HASHTABLE_SIZE] = {NULL};

node *head = NULL;

// Need a word counter to use in size
int wordCounter = 0;

// hash function
// Credit to Neel Mehta https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
unsigned int hash_word(const char *word)
{
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % HASHTABLE_SIZE;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    // Assigning what bucket the word will fall into
    unsigned int hash = hash_word(word);

    // cursor will point to bucket the word will be in
    node *cursor = hashtable[hash];

    while (cursor != NULL)
    {
        // do something
        if ((strcasecmp(cursor->word, word)) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }

    // Create char * array pointer to store a word in
    char word[LENGTH + 1];


    while (fscanf(file, "%s ", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            strcpy(new_node->word, word);
            // if this node is the last node, point to NULL
            new_node->next = NULL;

            unsigned int hash = hash_word(word);

            new_node->next = hashtable[hash];
            hashtable[hash] = new_node;

            wordCounter++;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node *cursor = hashtable[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}