#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define DEV false

void **all_pointers = NULL;
int amount_pointers = 0;

void dummy(void) { ; }
void free_all(void);
void free_one(void *ptr);
void check_alloc(void *suspected_pointer);

void solve_quadratic(double a, double b, double c);
void swap(void **item1, void **item2);

int main(void)
{
    double a, b, c = 0;
    scanf("%lf %lf %lf", &a, &b, &c);

    solve_quadratic(a, b, c);

    if (DEV == true)
    {
        free_all();
    }
    return 0;
}

void solve_quadratic(double a, double b, double c)
{

    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
            {
                printf("x\\in\\mathbb{R}\n");
            }
            else
            {
                printf("No solution.\n");
            }
        }
        else
        {
            double x = -c / b;
            printf("x = %.3lf\n", x);
        }
    }
    else
    {
        
        double *x1 = malloc(sizeof(double));
        check_alloc(x1);
        double *x2 = malloc(sizeof(double));
        check_alloc(x2);
        double delta = b * b - 4 * a * c;

        // Check the value of the discriminant to determine the number of roots
        if (delta > 0)
        {
            *x1 = (-b + sqrt(delta)) / (2 * a);
            *x2 = (-b - sqrt(delta)) / (2 * a);

            if (*x1 > *x2)
            {
                swap((void *)&x1, (void *)&x2);
            }

            printf("x1 = %.3lf, x2 = %.3lf\n", *x1, *x2);
        }
        else if (delta == 0)
        {
            double x0 = (-b) / (2 * a);
            printf("x1 = x2 = %.3lf\n", x0);
        }
        else
        {
            printf("No solution.\n");
        }

        free_one(x1);
        free_one(x2);
    }
}

// !!! Make sure that the input pointer are originally the same type when
// use this function.
void swap(void **item1, void **item2)
{
    void *tmp_ptr = *item1;
    *item1 = *item2;
    *item2 = tmp_ptr;
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
