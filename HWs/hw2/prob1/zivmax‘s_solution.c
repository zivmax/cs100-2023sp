#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void **all_pointers = NULL;
int amount_pointers = 0;
int DEV = false;

void free_all(void);
void check_alloc(void *suspected_pointer);

int *get_ints(int *num_of_ints);
long *reverse_positive_squares(int *arr, int len, int *new_len);

int main(void)
{
    int length_ints = 0;
    int *inputs = get_ints(&length_ints);

    int length_square = 0;
    long *squares = reverse_positive_squares(inputs, length_ints, &length_square);

    if (length_square != 0)
    {
        for (int i = 0; i < length_square; i++)
        {
            printf("%li\n", squares[i]);
        }
        printf("%i\n", length_square);
    }
    else
    {
        printf("No positive integers.\n");
    }

    free_all();
    return 0;
}

// A function that reads in a number of integers from the user input and returns
// them as an array of integers
int *get_ints(int *num_of_ints)
{
    scanf("%i", num_of_ints);

    int *arr = malloc(*num_of_ints * sizeof(int));
    check_alloc(arr);

    // Loop through the array and read in each integer from the user input
    for (int i = 0; i < *num_of_ints; i++)
    {
        int successes = scanf("%i", &arr[i]);

        // If the input was not a valid integer, decrement i to re-prompt the user for the same element
        if (successes == 0)
        {
            i--;
        }
    }

    return arr;
}

// A function that takes an array of integers, its length, and a pointer to a new length,
// and returns a new array containing the squares of the positive integers in the original
// array in reversed order
long *reverse_positive_squares(int *arr, int len, int *new_len)
{
    *new_len = 0;

    // Find the number of positive integers in the original array
    for (int i = 0; i < len; i++)
    {
        if (arr[i] > 0)
        {
            (*new_len)++;
        }
    }

    // Allocate memory for the new array
    long *new_arr = malloc((*new_len) * sizeof(long));
    check_alloc(new_arr);

    // Fill the new array with the squares of the positive integers in the original array in reversed order
    for (int i = len - 1, j = 0; i >= 0; i--)
    {
        if (arr[i] > 0)
        {
            new_arr[j] = (long) arr[i] * (long) arr[i];
            j++;
        }
    }

    return new_arr;
}

void free_all(void)
{
    if (DEV == true)
    {
        printf("\n\nFreeing All...\n");
    }
    for (int i = 0; i < amount_pointers; i++)
    {
        free(all_pointers[i]);
        if (DEV == true)
        {
            printf("Freed pointer-%i: %p\n", i + 1, all_pointers[i]);
        }
    }
}

void check_alloc(void *suspected_pointer)
{
    if (suspected_pointer == NULL)
    {
        if (all_pointers != NULL)
        {
            free_all();
            free(all_pointers);
        }
        printf("Failed to allocate memory.\n\n");
        exit(1);
    }
    else
    {
        amount_pointers++;
        all_pointers = realloc(all_pointers, amount_pointers * sizeof(void *));
        all_pointers[amount_pointers - 1] = suspected_pointer;
    }
}
