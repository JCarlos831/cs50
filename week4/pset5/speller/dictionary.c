// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// node *node1 = malloc(sizeof(node));

int HASHTABLE_SIZE = 65536;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    // hashtable[hash(word)];

    // node *cursor = node1;
    // while (cursor != NULL)
    // {
    //     // do something
    //     // strcmp?
    //     cursor = cursor->next;
    // }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    while (fscanf(file, "%s\n", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            // hash function
            // credit to delipity at https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/#bottom-comments
            int hash_it(char* word)
            {
                unsigned int hash = 0;
                for (int i=0, n=strlen(word); i<n; i++)
                    hash = (hash << 2) ^ tolower(word[i]);
                return hash % HASHTABLE_SIZE;
            }

            node *hashtable[HASHTABLE_SIZE];

            strcpy(new_node->word, word);
            new_node->next = node1;
            node1 = new_node;
        }
    }
    fclose(file);
    return true;


}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // node *cursor = node1;

    // while (cursor != NULL)
    // {
    //     node *temp = cursor;
    //     cursor = cursor->next;
    //     free(temp);
    // }
    // return false;
}