#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEV false

#define ROWS 9
#define COLS 9

void **all_pointers = NULL;
int amount_pointers = 0;

void dummy(void) { ; }
void free_all(void);
void free_one(void *ptr);
void check_alloc(void *suspected_pointer);
void freed_exit(void);

void get_grid(int ***board);
bool checkOneNumber(int **board, int row, int col);

int main(void)
{
    int **board = NULL;

    // Read in the Sudoku board from standard input.
    get_grid(&board);

    // Check each grid in the Sudoku board.
    for (int j = 0; j < ROWS; j++)
    {
        for (int i = 0; i < COLS; i++)
        {
            if (!checkOneNumber(board, j, i))
            {
                // If any number is invalid, output 0 and return.
                printf("0\n");
                freed_exit();
            }
        }
    }

    // If all numbers are valid, output 1 and return.
    printf("1\n");
    for (int i = 0; i < COLS; i++)
    {
        free_one(board[i]);
    }
    free_one(board);
    freed_exit();
}

void get_grid(int ***board)
{
    *board = malloc(ROWS * sizeof(int *));
    check_alloc(*board);

    for (int i = 0; i < COLS; i++)
    {
        (*board)[i] = malloc(COLS * sizeof(int *));
        check_alloc((*board)[i]);
    }

    for (int j = 0; j < ROWS; j++)
    {
        for (int i = 0; i < COLS; i++)
        {
            scanf("%d", &(*board)[j][i]);
        }
    }
}

bool checkBlock(int **board, int block_row, int block_col)
{
    bool *used = calloc(10, sizeof(bool));
    check_alloc(used);

    for (int j = block_row * 3; j < (block_row + 1) * 3; j++)
    {
        for (int i = block_col * 3; i < (block_col + 1) * 3; i++)
        {
            int num = board[j][i];
            if (num != 0 && used[num])
            {
                return false;
            }
            else
            {
                used[num] = true;
            }
        }
    }

    free_one(used);
    return true;
}

bool checkOneNumber(int **board, int row, int col)
{
    // Check 3x3 bolck.
    for (int j = 0; j < (ROWS / 3); j++)
    {
        for (int i = 0; i < (COLS / 3); i++)
        {
            if (!checkBlock(board, j, i))
            {
                return false;
            }
        }
    }

    // Check row.
    for (int i = 0; i < COLS; i++)
    {
        if (board[row][i] == board[row][col] && i != col)
        {
            return false;
        }
    }

    // Check col.
    for (int j = 0; j < ROWS; j++)
    {
        if (board[j][col] == board[row][col] && j != row)
        {
            return false;
        }
    }
    // Check horse-step.
    for (int l = row - 2; abs(l - row) <= 2; l++)
    {
        for (int k = col - 2; abs(k - col) <= 2; k++)
        {
            if (l < 0 || k < 0 || l >= 9 || k >= 9)
            {
                continue;
            }

            if ((abs(l - row) == 2 && abs(k - col) == 1) || (abs(l - row) == 1 && abs(k - col) == 2))
            {
                if (board[l][k] == board[row][col])
                {
                    return false;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    return true;
}

void free_one(void *ptr)
{
    for (int i = 0; i < amount_pointers; i++)
    {
        if (all_pointers[i] == ptr)
        {
            free(ptr);
            all_pointers[i] = NULL;
        }
    }
}

void free_all(void)
{
    if (DEV == true)
    {
        printf("\n\nFreeing All...\n");
    }
    if (all_pointers != NULL)
    {
        for (int i = 0; i < amount_pointers; i++)
        {
            if (all_pointers[i] != NULL)
            {
                free(all_pointers[i]);
                if (DEV == true)
                {
                    printf("Freed pointer-%i: %p\n", i + 1, all_pointers[i]);
                }
            }
            else
            {
                printf("pointer-%i has been freed manually.\n", i + 1);
            }
        }
        free(all_pointers);
    }
    else
    {
        if (DEV == true)
        {
            printf("No pointer needs to be freed.\n");
        }
    }
}

void check_alloc(void *suspected_pointer)
{
    if (suspected_pointer == NULL)
    {
        printf("Failed to allocate memory.\n\n");
        free_all();
        exit(1);
    }
    else
    {
        amount_pointers++;
        all_pointers = realloc(all_pointers, amount_pointers * sizeof(void *));
        if (all_pointers == NULL)
        {
            free_all();
        }

        all_pointers[amount_pointers - 1] = suspected_pointer;
    }
}

void freed_exit(void)
{
    if (DEV == true)
    {
        free_all();
    }
    else
    {
        free_one(all_pointers);
    }
    exit(0);
}
