#include <stdio.h>
#include <stdlib.h>

void print_binary(unsigned long n);
int get_lenght_bin(unsigned long n);
void print_bin(unsigned long n);

int main(void)
{
    unsigned long x, y, p, q;
    x = p = q = 0;

    int m, lowbit;
    lowbit = m = 0;

    scanf("%lu %d", &x, &m);

    // Split
    q = x >> (m + 1);
    p = x - (q << (m + 1));

    // Combine
    y = (p << (get_lenght_bin(q))) | q;

    // Compute lowbit
    lowbit = (get_lenght_bin(y & (~y + 1)) - 1);

    printf("%lu %i\n", y, lowbit);
    return 0;
}

int get_lenght_bin(unsigned long n)
{
    int count = 0;
    while (n > 0)
    {
        n = n >> 1;
        count++;
    }
    return count;
}

void print_bin(unsigned long n)
{
    print_binary(n);
    printf("\n");
}

void print_binary(unsigned long n)
{
    if (n > 1)
    {
        print_binary(n >> 1);
    }
    printf("%lu", n & 1);
}
