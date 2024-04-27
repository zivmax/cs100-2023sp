#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define X 0
#define Y 1


int **get_input(void);
double *caculate_k(int *point_1, int *point_2);
double *caculate_b(int *point_1, int *point_2, double *k);
void free_all(int **points, double *k, double *b);


int main(void)
{
    // Call the get_input function to get the coordinates of two points.
    int **points = get_input();
    if (points == NULL)
    {
        // If the get_input function fails, free any memory that was allocated and return an error code.
        return 1;
    }

    // Calculate the slope (k) of the line passing through the two points.
    double *k = caculate_k(points[0], points[1]);
    if (k == NULL)
    {
        // If the calculate_k function fails, free any memory that was allocated and return an error code.
        free(points[0]);
        free(points[1]);
        free(points);
        return 2;
    }

    // Calculate the y-intercept (b) of the line passing through the two points.
    double *b = caculate_b(points[0], points[1], k);
    if (b == NULL)
    {
        // If the calculate_b function fails, free any memory that was allocated and return an error code.
        free(points[0]);
        free(points[1]);
        free(points);
        free(k);
        return 3;
    }

    // Print the equation of the line in the form "y = kx + b" or "x = b" if the line is vertical.
    if (k[1] == 1)
    {
        printf("x = %.2lf\n", *b);
    }
    else
    {
        int b_state = 0;
        if (*b > 0 || *b == 0)
        {
            b_state = 1;
        }

        switch (b_state)
        {
        case 1:
            printf("y = %.2lfx + %.2lf\n", *k, *b);
            break;
        case 0:
            printf("y = %.2lfx - %.2lf\n", *k, -*b);
            break;
        }
    }

    // Free all dynamically allocated memory before exiting the program.
    free_all(points, k, b);
    return 0;
}


int **get_input(void)
{
    // Allocate memory for two integer pointers, each of which will store x and y coordinates of a point.
    int *point_1 = malloc(2 * sizeof(int));
    int *point_2 = malloc(2 * sizeof(int));

    // Check if the memory allocation was successful.
    if (point_1 == NULL || point_2 == NULL)
    {
        printf("Falied to malloc!\n");
        return NULL;
    }

    // Read in the x and y coordinates for the first point in the format of "(x, y)".
    scanf("(%d, %d)\n", &point_1[X], &point_1[Y]);

    // Read in the x and y coordinates for the second point in the format of "(x, y)".
    scanf("(%d, %d)", &point_2[X], &point_2[Y]);

    // If the two points have the same coordinates, prompt the user to enter a different second point.
    while (point_1[X] == point_2[X] && point_1[Y] == point_2[Y])
    {
        scanf("(%d, %d)", &point_2[X], &point_2[Y]);
    }

    // Allocate memory for an array of two integer pointers.
    int **points = malloc(2 * sizeof(int *));
    if (points == NULL)
    {
        printf("Falied to malloc!\n");
        // Free the previously allocated memory if the new allocation fails.
        free(point_1);
        free(point_2);
        return NULL;
    }

    // Store the two integer pointers in the array.
    points[0] = point_1;
    points[1] = point_2;

    // Return the array of two integer pointers.
    return points;
}

double *caculate_k(int *point_1, int *point_2)
{
    // Allocate memory for a double pointer to store the slope values of the line.
    double *k = malloc(2 * sizeof(double));

    // Set the second value of the array to 0 by default.
    k[1] = 0;

    // Check if the memory allocation was successful.
    if (k == NULL)
    {
        printf("Falied to malloc!\n");
        return NULL;
    }

    // If the two points have the same x-coordinate, the slope is undefined.
    if (point_1[X] == point_2[X])
    {
        // Set the first value of the array to 0 and the second value to 1 to indicate an undefined slope.
        k[0] = 0;
        k[1] = 1;
        return k;
    }

    // Calculate the slope of the line connecting the two points using the formula (y2 - y1) / (x2 - x1).
    *k = (point_1[Y] - point_2[Y]) / (double)(point_1[X] - point_2[X]);

    // If the slope is very small, treat it as 0 to avoid numerical precision errors.
    if (*k == 0)
    {
        *k = 0;
    }

    // Return the pointer to the array of slope values.
    return k;
}

double *caculate_b(int *point_1, int *point_2, double *k)
{
    // allocate space in memory for b_tmp
    double *b_tmp = malloc(2 * sizeof(double));

    // check if malloc failed
    if (b_tmp == NULL)
    {
        printf("Falied to malloc!\n");
        return NULL;
    }

    // check if k[1] is equal to 0
    if (k[1] == 0)
    {
        // calculate b_tmp[0] based on point_1[Y] and k[0]*point_1[X]
        b_tmp[0] = point_1[Y] - (k[0] * point_1[X]);
        // calculate b_tmp[1] based on point_2[Y] and k[0]*point_2[X]
        b_tmp[1] = point_2[Y] - (k[0] * point_2[X]);
    }
    else
    {
        // set b_tmp[0] to point_1[X]
        b_tmp[0] = point_1[X];
        // set b_tmp[1] to point_2[X]
        b_tmp[1] = point_2[X];
    }

    // check if b_tmp[0] and b_tmp[1] have the same value
    if ( (int) b_tmp[0] == (int) b_tmp[1])
    {
        // allocate space in memory for b
        double *b = malloc(1 * sizeof(double));
        // set value of b to b_tmp[0]
        *b = b_tmp[0];
        // free the memory allocated for b_tmp
        free(b_tmp);
        // return the value of b
        return b;
    }
    else
    {
        printf("Can't calculate b!\n");
        // free the memory allocated for b_tmp
        free(b_tmp);
        // return NULL since b can't be calculated
        return NULL;
    }
}


void free_all(int **points, double *k, double *b)
{
    free(points[0]);
    free(points[1]);
    free(points);
    free(k);
    free(b);
}
