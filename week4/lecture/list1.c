// implements a list of unique numbers using an array of dynamic length

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // memory for numbers
    int *numbers = NULL;
    int capacity = 0;

    // Prompt for numbers (until EOF)
    int size = 0;
    while (true)
    {
        // Prompt for number
        int number = get_int("number: ");

        // check for EOF
        if (number == INT_MAX)
        {
            break;
        }

        // check whether number is already in list
        bool found = false;
        for (int i = 0; i < size; i+)
        {
            if (numbers[i] == number)
            {
                found = true;
                break;
            }
        }

        // if number not found in list, add to list
        if (!found)
        {
            // check whether enough space for number
            if (size == capacity)
            {
                // allocate space for number
                numbers = realloc(numbers, sizeof(int) * (size + 1));
                if (!numbers)
                {
                    return 1;
                }
                capacity++;
            }

            // add nubmer to list
            numbers[size] = number;
            size++;
        }
    }

    //Print numbers
    for (int i = 0; i < size; i++)
    {
        printf("%i\n", numbers[i]);
    }
}