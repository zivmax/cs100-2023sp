#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int total_games = 0, total_cost = 0;
    int type_1st = 0, cost_1st = 0;
    int type = 0, price = 0;


    // Get the total number of games and calculate the total cost
    scanf("%d", &total_games);
    int *cost_table = calloc(1000000 + 1, sizeof(int));

    for (int i = 1; i <= total_games; i++)
    {
        scanf(" (%*[^,],%d,%d)", &price, &type);
        total_cost += price;

        cost_table[type] += price;

        do
        {
            if (type == type_1st)
            {
                cost_1st = cost_table[type];
                break;
            }

            else if ((2 * cost_table[type]) >= total_cost)
            {
                type_1st = type;
                cost_1st = cost_table[type];
                break;
            }

            else if (cost_table[type] > cost_1st)
            {
                type_1st = type;
                cost_1st = cost_table[type];
                break;
            }
        }
        while (0);
    }
    printf("%d\n", type_1st);
    free(cost_table);
    return 0;
}
