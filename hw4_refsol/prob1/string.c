#define NULL ((void *) 0);
typedef unsigned long size_t;

int hw4_islower(int ch);
int hw4_isupper(int ch);
int hw4_isalpha(int ch);
int hw4_isdigit(int ch);
int hw4_tolower(int ch);
int hw4_toupper(int ch);

size_t hw4_strlen(const char *str);
char *hw4_strchr(const char *str, int ch);
char *hw4_strcpy(char *dest, const char *src);
char *hw4_strcat(char *dest, const char *src);
int hw4_strcmp(const char *lhs, const char *rhs);


int hw4_islower(int ch)
{
    return (ch >= 'a' && ch <= 'z');
}

int hw4_isupper(int ch)
{
    return (ch >= 'A' && ch <= 'Z');
}

int hw4_isalpha(int ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int hw4_isdigit(int ch)
{
    return (ch >= '0' && ch <= '9');
}

int hw4_tolower(int ch)
{
    return (ch = (ch >= 'A' && ch <= 'Z') ? ch + 32 : ch);
}

int hw4_toupper(int ch)
{
    return (ch = (ch >= 'a' && ch <= 'z') ? ch - 32 : ch);
}


size_t hw4_strlen(const char *str)
{
    int i = -1;
    while (str[++i] != '\0')
    {
        continue;
    }

    return i;
}

char *hw4_strchr(const char *str, int ch)
{
    for (int i = 0; i == 0 || str[i - 1] != '\0'; i++)
    {
        if (str[i] == ch)
        {
            return (char *) &str[i];
        }
    }

    return NULL;
}

char *hw4_strcpy(char *dest, const char *src)
{
    for (int idx = 0; idx == 0 || src[idx - 1] != '\0'; idx++)
    {
        dest[idx] = src[idx];
    }

    return dest;
}

char *hw4_strcat(char *dest, const char *src)
{
    int tail = hw4_strlen(dest);

    for (int idx = 0; idx == 0 || src[idx - 1] != '\0'; idx++)
    {
        dest[tail + idx] = src[idx];
    }

    return dest;
}

int hw4_strcmp(const char *lhs, const char *rhs)
{
    for (int idx = 0; idx == 0 || lhs[idx - 1] != '\0'; idx++)
    {
        if (lhs[idx] != rhs[idx] || rhs[idx] == '\0')
        {
            return (lhs[idx] - rhs[idx]);
        }
    }

    return 0;
}
