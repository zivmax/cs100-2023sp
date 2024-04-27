#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

int main()
{
    int mon = 0;
    scanf("%d ", &mon);

    int *mons = calloc(mon + 1, sizeof(int));
    mons[0] = mon;

    for (int i = 1; i <= mon; i++)
    {
        scanf("%d ", &mons[i]);
    }

    int YYYY1 = 0, MM1 = 0, DD1 = 0;
    scanf("%4d%2d%2d", &YYYY1, &MM1, &DD1);
    int YYYY2 = 0, MM2 = 0, DD2 = 0;
    scanf("%4d%2d%2d", &YYYY2, &MM2, &DD2);


    int count = 0;
    short left_part = 0;

    for (int month = 1; month <= mon; month++)
    {
        for (int day = 1; day <= mons[month]; day++)
        {
            left_part = (day % 10) * 1000 + (day / 10) * 100 + (month % 10) * 10 + month / 10;

            if (left_part >= YYYY1 && left_part <= YYYY2)
            {
                if (left_part == YYYY1)
                {
                    if ((month == MM1 && day < DD1) || month < MM1)
                    {
                        continue;
                    }
                }
                else if (left_part == YYYY2)
                {
                    if ((month == MM2 && day > DD2) || month > MM2)
                    {
                        continue;
                    }
                }

                count++;
            }
        }
    }
    printf("%d\n", count);

    free(mons);
    return 0;
}
