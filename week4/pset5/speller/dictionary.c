// implements a dictionary's functionality

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

// set hashtable to NULL
node *hashtable[HASHTABLE_SIZE] = {NULL};

// set head to NULL
node *head = NULL;

// need a word counter to use in size
int wordCounter = 0;

// hash function
// credit to Neel Mehta https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
unsigned int hash_word(const char *word)
{
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % HASHTABLE_SIZE;
}

// returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    // assigning what bucket the word will fall into
    unsigned int hash = hash_word(word);

    // cursor will point to bucket the word will be in
    node *cursor = hashtable[hash];

    // loop that advances as long as the cursor is not null
    while (cursor != NULL)
    {
        // search node in the linked list to see if word is in the dictionary
        if ((strcasecmp(cursor->word, word)) == 0)
        {
            // if found, return true
            return true;
        }
        else
        {
            // advance to next node
            cursor = cursor->next;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file and give it read privilege
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }

    // Create char * array pointer to store a word in
    char word[LENGTH + 1];

    // scan dictionary word by word until end of dictionary file
    while (fscanf(file, "%s ", word) != EOF)
    {
        // allocate enough space in memory to store node
        node *new_node = malloc(sizeof(node));

        // check to make sure that the pointer to the node doesn't return NULL
        if (new_node == NULL)
        {
            // unload dictionary
            unload();
            // return false so that the speller quits
            return false;
        }
        else
        {
            // copy word into node
            strcpy(new_node->word, word);

            // if this node is the last node, point to NULL
            new_node->next = NULL;

            unsigned int hash = hash_word(word);

            // point new node next to the pointer that head is pointing to
            new_node->next = hashtable[hash];

            // reassign head pointer to new node
            hashtable[hash] = new_node;

            // increase word count
            wordCounter++;
        }
    }
    // close dictionary
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

    // free linked lists from hash table
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // code from Zamyla's walkthrough to free linked lists
        node *cursor = hashtable[i];

        // loop that advances as long as the cursor is not null
        while (cursor != NULL)
        {
            // set up a temporary node pointer
            node *temp = cursor;

            // advance the cursor
            cursor = cursor->next;

            // free the temporary node pointer
            free(temp);
        }
    }
    return true;
}