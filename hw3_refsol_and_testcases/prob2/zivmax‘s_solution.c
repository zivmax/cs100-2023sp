#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEV false

void **all_pointers = NULL;
int amount_pointers = 0;

void dummy(void) { ; }
void free_one(void *ptr);
void free_all(void);
void check_alloc(void *suspected_pointer);
void *malloc_checked(unsigned long size);
void *calloc_checked(unsigned long number, short type_size);
void *realloc_checked(void *old_pointer, unsigned long size);
void exit_freed(int exit_code);


#define ALPHABET_SIZE 26

void get_intput(char *key, char *text);
char *generate_encode_key(char *keyword);
char *generate_decode_key(char *encode_key);
void decode_text_and_print(const char *text, char *decode_key);

int main(void)
{
    char *keyword = calloc_checked(101, sizeof(char));
    char *text = calloc_checked(1000001, sizeof(char));
    get_intput(keyword, text);


    char *encode_key = generate_encode_key(keyword);
    char *decode_key = generate_decode_key(encode_key);


    decode_text_and_print(text, decode_key);
    exit_freed(0);
}

void get_intput(char *key, char *text)
{
    scanf("%s\n", key);

    char c = 0;
    int i = 0;
    while ((c = getc(stdin)) != EOF && c != '\n')
    {
        text[i] = c;
        i++;
    }
}


int check_all_alphabet(int *existed)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (!existed[i])
        {
            return 0;
        }
    }
    return 1;
}

char *generate_encode_key(char *keyword)
{
    int existed[ALPHABET_SIZE] = {0};

    char *encode_key = calloc_checked(ALPHABET_SIZE, sizeof(int));

    char *lower_keyword = calloc_checked(strlen(keyword) + 1, sizeof(char));

    for (int i = 0; keyword[i] != '\0'; i++)
    {
        lower_keyword[i] = tolower(keyword[i]);
    }
    lower_keyword[strlen(keyword)] = '\0';

    int header = 0;
    char alphabet[ALPHABET_SIZE + 1] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; lower_keyword[i] != '\0'; i++)
    {
        char current_char = lower_keyword[i];

        if (!existed[current_char - 'a'])
        {
            encode_key[header] = current_char;
            short idx = current_char - 'a';
            existed[idx] = 1;
            header++;
        }

        if (check_all_alphabet(existed) == 1)
        {
            return encode_key;
        }
    }

    for (int i = encode_key[header - 1] - 'a' + 1; 1; i++)
    {
        if (i == 26)
        {
            i = 0;
        }

        char current_char = alphabet[i];

        if (!existed[current_char - 'a'])
        {
            encode_key[header] = current_char;
            short idx = current_char - 'a';
            existed[idx] = 1;
            header++;
        }

        if (check_all_alphabet(existed) == 1)
        {
            return encode_key;
        }
    }

    return NULL;
}

char *generate_decode_key(char *encode_key)
{
    char *decode_key = calloc_checked(ALPHABET_SIZE, sizeof(int));

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        int index = encode_key[i] - 'a';
        decode_key[index] = i + 'a';
    }

    return decode_key;
}

void decode_text_and_print(const char *text, char *decode_key)
{
    int i = 0;
    while (text[i] != '\0')
    {
        char c = text[i];
        if (isupper(c))
        {
            c = toupper(decode_key[c - 'A']);
        }
        else if (islower(c))
        {
            c = decode_key[c - 'a'];
        }
        putchar(c);
        i++;
    }
    putchar('\n');
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

void *malloc_checked(unsigned long size)
{
    if ((int) size > 0)
    {
        void *new_pointer = malloc(size);
        check_alloc(new_pointer);

        return new_pointer;
    }
    else
    {
        printf("Invalid size for malloc_checked.");
        exit_freed(1);
    }

    return NULL;
}


void *calloc_checked(unsigned long number, short type_size)
{
    if ((int) number * type_size > 0)
    {
        void *new_pointer = calloc(number, type_size);
        check_alloc(new_pointer);

        return new_pointer;
    }
    else
    {
        printf("Invalid size for calloc_checked.");
        exit_freed(1);
    }

    return NULL;
}


void *realloc_checked(void *old_pointer, unsigned long size)
{
    if ((int) size < 0)
    {
        printf("Invalid size for realloc_checked.");
        exit_freed(1);
    }


    int idx = -1;
    if (old_pointer != NULL)
    {
        for (int i = 0; i < amount_pointers; i++)
        {
            if (all_pointers[i] == old_pointer)
            {
                all_pointers[i] = NULL;
                idx = i;
            }
        }
    }

    if (idx != -1)
    {
        void *new_pointer = realloc(old_pointer, size);
        all_pointers[idx] = new_pointer;

        return new_pointer;
    }
    else if (old_pointer == NULL)
    {
        void *new_pointer = malloc_checked(size);

        return new_pointer;
    }
    else
    {
        printf("Try to realloc_checked a illegal pointer.");
        exit_freed(1);
    }

    return NULL;
}


void exit_freed(int exit_code)
{
    if (DEV == true)
    {
        free_all();
    }
    else
    {
        free_one(all_pointers);
    }
    exit(exit_code);
}
