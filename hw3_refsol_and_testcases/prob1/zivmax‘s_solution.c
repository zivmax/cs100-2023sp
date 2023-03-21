#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *get_string(void);
void get_intput(int *key, char text[]);
int check_type(char character);


int main(void)
{
    int key = 0;
    char text[1000000] = {0};

    get_intput(&key, text);

    int i = 0;
    while (text[i] != '\0')
    {
        int type = check_type(text[i]);

        if (type == -1)
        {
            i++;
            continue;
        }

        int ascii = 0;
        switch (type)
        {
            case 0:
            {
                ascii = text[i] - key % 10;
                text[i] = (ascii >= '0' && ascii <= '9') ? ascii : (text[i] - '0' - key % 10 + 10) % 10 + '0';
                break;
            }

            case 1:
            {
                ascii = text[i] - key % 26;
                text[i] = (ascii >= 'a' && ascii <= 'z') ? ascii : (text[i] - 'a' - key % 26 + 26) % 26 + 'a';
                break;
            }
            case 2:
            {
                ascii = text[i] - key % 26;
                text[i] = (ascii >= 'A' && ascii <= 'Z') ? ascii : (text[i] - 'A' - key % 26 + 26) % 26 + 'A';
                break;
            }
        }
        i++;
    }

    printf("%s\n", text);

    return 0;
}

void get_intput(int *key, char text[])
{
    scanf("%d ", key);
    char c = 0;
    int i = 0;
    while ((c = getc(stdin)) != EOF && c != '\n')
    {
        text[i] = c;
        i++;
    }
}

int check_type(char character)
{
    if (isdigit(character))
    {
        return 0;
    }
    else if (islower(character))
    {
        return 1;
    }
    else if (isupper(character))
    {
        return 2;
    }
    else
    {
        return -1;
    }
}
