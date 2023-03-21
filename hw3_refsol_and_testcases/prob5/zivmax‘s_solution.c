#include <stdio.h>
#include <stdlib.h>

char refer[7][7] = {
    {'0', '0', '0', 'U', '0', '0', '0'},
    {'0', '0', 'L', 'f', 'R', '0', '0'},
    {'0', 'L', '0', 'D', '0', 'R', '0'},
    {'D', 'l', 'U', '0', 'U', 'r', 'D'},
    {'0', 'R', '0', 'D', '0', 'L', '0'},
    {'0', '0', 'R', 'b', 'L', '0', '0'},
    {'0', '0', '0', 'U', '0', '0', '0'}
};


int main(void)
{
    int row = 0, col = 0, hints_number = 0;
    scanf("%d %d %d", &row, &col, &hints_number);

    short **found = calloc(row, sizeof(short *));
    char **matrix_hamster = calloc(row, sizeof(char *));
    for (int i = 0; i < row; i++)
    {
        matrix_hamster[i] = calloc(col, sizeof(char));
        found[i] = calloc(col, sizeof(short));
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            scanf(" %c", &matrix_hamster[i][j]);
        }
    }

    int row_1st, col_1st;
    scanf(" %d %d", &row_1st, &col_1st);

    int **hints = calloc(hints_number, sizeof(int *));
    for (int i = 0; i < hints_number; i++)
    {
        hints[i] = calloc(2, sizeof(int));
    }

    char hint_tmp = '\0';
    for (int i = 0; i < hints_number; i++)
    {
        scanf(" %c%*[a-z] %d", &hint_tmp, &hints[i][1]);
        hints[i][0] = (int) hint_tmp;
    }


    char operate = '0';
    int move_refer[2] = {0};
    int header[2] = {row_1st - 1, col_1st - 1};

    for (int i = 0; i < hints_number; i++)
    {
        switch (matrix_hamster[header[0]][header[1]])
        {
            case 'U':
                move_refer[0] = 1;
                move_refer[1] = 3;
                break;
            case 'D':
                move_refer[0] = 5;
                move_refer[1] = 3;
                break;
            case 'L':
                move_refer[0] = 3;
                move_refer[1] = 1;
                break;
            case 'R':
                move_refer[0] = 3;
                move_refer[1] = 5;
                break;
            default:
                break;
        }

        switch (hints[i][0])
        {
            case 'F':
                operate = refer[move_refer[0] - 1][move_refer[1]];
                break;
            case 'B':
                operate = refer[move_refer[0] + 1][move_refer[1]];
                break;
            case 'L':
                operate = refer[move_refer[0]][move_refer[1] - 1];
                break;
            case 'R':
                operate = refer[move_refer[0]][move_refer[1] + 1];
                break;
            default:
                printf("Unknown error.\n");
                return 1;
        }

        switch (operate)
        {
            case 'U':
                header[0] -= hints[i][1];
                break;
            case 'D':
                header[0] += hints[i][1];
                break;
            case 'L':
                header[1] -= hints[i][1];
                break;
            case 'R':
                header[1] += hints[i][1];
                break;
            default:
                printf("Unknown error.\n");
                return 1;
        }

        if (header[0] >= 0 && header[0] < row && header[1] >= 0 && header[1] < col)
        {
            if (!found[header[0]][header[1]])
            {
                found[header[0]][header[1]] = 1;
                printf("(%d, %d)\n", header[0] + 1, header[1] + 1);
            }
            else
            {
                printf("Mistake!\n");
                break;
            }
        }
        else
        {
            printf("Mistake!\n");
            break;
        }
    }

    for (int i = 0; i < row; i++)
    {
        free(matrix_hamster[i]);
        free(found[i]);
    }
    free(matrix_hamster);
    free(found);

    for (int i = 0; i < hints_number; i++)
    {
        free(hints[i]);
    }
    free(hints);


    return 0;
}
