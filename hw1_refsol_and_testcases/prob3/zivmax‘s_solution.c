#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void dummy(void) { ; }

char *str_numbers[] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten"};
char *str_teens[] = {
    "eleven",
    "twelve",
    "thirteen",
    "fourteen",
    "fifteen",
    "sixteen",
    "seventeen",
    "eighteen",
    "nineteen"};
char *str_num_words[] = {
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety",
    "hundred",
    "thousand"};

int *extract_digits_reverse(long number, int *length);
void handle_numbers(char **words, int *num);
void handle_teens(char **words, int *num);
void handle_num_words(char **words, int *digits, int length);

int main(void)
{
    int num = 0;
    char *words = NULL;
    scanf("%d", &num);

    int length = 0;
    int *digits = extract_digits_reverse(num, &length);

    if (num < 0)
    {
        return 1;
    }
    if (num == 0)
    {
        words = malloc(5 * sizeof(char));
        sprintf(words, "zero");
    }
    else if (num <= 10)
    {
        handle_numbers(&words, digits);
    }
    else if (num <= 19)
    {
        handle_teens(&words, digits);
    }
    else
    {
        handle_num_words(&words, digits, length);
    }
    printf("%s\n", words);
    free(words);
    free(digits);

    return 0;
}

int *extract_digits_reverse(long number, int *length)
{
    *length = 0;
    long temp = number;
    if (number == 0)
    {
        *length = 1;
    }
    while (temp != 0)
    {
        *length = *length + 1;
        temp /= 10;
    }
    int *digits = malloc(*length * sizeof(int));
    if (digits == NULL)
    {
        exit(1);
    }
    for (int i = 0; i < *length; i++)
    {
        digits[i] = number % 10;
        number /= 10;
    }
    return digits;
}

void handle_numbers(char **words, int *digits)
{
    *words = malloc(6 * sizeof(char));
    if (*words == NULL)
    {
        exit(1);
    }

    if (digits[0] == 0 && digits[1] == 1)
    {
        sprintf(*words, "%s", str_numbers[10]);
    }
    else
    {
        sprintf(*words, "%s", str_numbers[digits[0]]);
    }
}

void handle_teens(char **words, int *digits)
{
    *words = malloc(30 * sizeof(char));
    if (*words == NULL)
    {
        exit(1);
    }
    sprintf(*words, "%s", str_teens[digits[0] - 1]);
}

void handle_teen_with_number(char **words, int *digits)
{

    *words = malloc(30 * sizeof(char));
    if (*words == NULL)
    {
        exit(1);
    }

    char *one_place = NULL;
    handle_numbers(&one_place, digits);

    if (digits[1] != 0)
    {
        char *ten_place = str_num_words[digits[1] - 2];
        if (digits[0] != 0)
        {
            sprintf(*words, "%s-%s", ten_place, one_place);
        }
        else
        {
            sprintf(*words, "%s", ten_place);
        }
    }
    else
    {
        sprintf(*words, "%s", one_place);
    }
    free(one_place);
}

void handle_hundred_words(char **words, int *digits)
{
    *words = malloc(40 * sizeof(char));
    if (*words == NULL)
    {
        exit(1);
    }

    char *ten_and_one_place = NULL;
    if (digits[1] == 1 && digits[0] >= 1 && digits[0] <= 9)
    {
        handle_teens(&ten_and_one_place, digits);
    }
    else if (digits[1] == 1 && digits[0] == 0)
    {
        ten_and_one_place = malloc(4 * sizeof(char));
        sprintf(ten_and_one_place, "ten");
    }
    else
    {
        handle_teen_with_number(&ten_and_one_place, digits);
    }



    char *hundred_place = NULL;
    handle_numbers(&hundred_place, &digits[2]);



    if (strcmp(hundred_place, "zero") && strcmp(hundred_place, "ten"))
    {
        if (strcmp(ten_and_one_place, "zero"))
        {
            sprintf(*words, "%s hundred and %s", hundred_place, ten_and_one_place);
        }
        else
        {
            sprintf(*words, "%s hundred", hundred_place);
        }
    }
    else
    {
        sprintf(*words, "%s", ten_and_one_place);
    }


    free(hundred_place);
    free(ten_and_one_place);

}

void handle_num_words(char **words, int *digits, int length)
{

    if (length <= 3)
    {
        switch (length)
        {
        case 2:
            handle_teen_with_number(words, digits);
            break;

        case 3:
            handle_hundred_words(words, digits);
            break;
        }
    }
    else
    {
        char *thousand_place = NULL;
        char *after_place = NULL;
        *words = malloc(80 * sizeof(char));
        switch (length)
        {
        case 4:
            handle_numbers(&thousand_place, &digits[3]);
            break;

        case 5:
            if (digits[4] == 1 && digits[3] > 0 && digits[3] <= 9)
            {
                handle_teens(&thousand_place, &digits[3]);
            }
            else if (digits[4] == 1 && digits[3] == 0)
            {
                thousand_place = malloc(4 * sizeof(char));
                sprintf(thousand_place, "ten");
            }
            else
            {
                handle_teen_with_number(&thousand_place, &digits[3]);
            }
            break;

        case 6:
            handle_hundred_words(&thousand_place, &digits[3]);
            break;
        }

        handle_hundred_words(&after_place, digits);

        if (!strcmp(after_place, "zero"))
        {
            sprintf(*words, "%s thousand", thousand_place);
        }
        else if (digits[2] == 0)
        {
            sprintf(*words, "%s thousand and %s", thousand_place, after_place);
        }
        else
        {
            sprintf(*words, "%s thousand %s", thousand_place, after_place);
        }


        free(thousand_place);
        free(after_place);
    }
}
