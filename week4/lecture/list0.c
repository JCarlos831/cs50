// Implements a list of unique numbers using an array of fixed length

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompt for number of numbers
    int capacity;
    do
    {
        capacity = get_int("capacity: ");
    }
    while (capacity < 1);

    // memory for numbers
    int numbers[capacity];

    // prompt for numbers
    int size = 0;
    while (size < capacity)
    {
        // prompt for number
        int number = get_int("number: ");

        // check whether number is already in list
        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if(numbers[i] == number)
            {
                found = true;
                break;
            }
        }

        // if number not found in list, add to list
        if (!found)
        {
            numbers[size] = number;
            size ++;
        }
    }

    //Print numbers
    for (int i = 0; i < size; i++)
    {
        printf("%i\n", numbers[i]);
    }
}