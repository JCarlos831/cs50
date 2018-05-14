// Implements a list of unique numbers using a linked list

#include <cs50.h>
#include <stdio.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    // memory for numbers
    node *numbers = NULL;

    // prompt for number (until EOF)
    while (true)
    {
        // prompt for number
        int number = get_int("number: ");

        // check for EOF
        if (number == INT_MAX)
        {
            break;
        }

        // check whether number is already in list
        bool found = false;
        for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->number == number)
            {
                found = true;
                break;
            }
        }

        // if number not found in list, add to list
        if (!found)
        {
            // allocate space for number
            node *n = malloc(sizeof(node));
            if (!n)
            {
                return 1;
            }

            // add number to list
            n->number = number;
            n->next = NULL;
            if (numbers)
            {
                for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
                {
                    if (!ptr->next)
                    {
                        ptr->next = n;
                        break;
                    }
                }
            }
            else
            {
                numbers = n;
            }
        }
    }

    // Print numbers
    printf("\n");
    for (node *ptr = numbers; ptr !=NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    // free memory
    node *ptr = numbers;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}