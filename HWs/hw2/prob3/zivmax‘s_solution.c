#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEV false

#define MAX_DIGITS 50

typedef struct node
{
    char digit;
    struct node *prev;
    struct node *next;
} node;

typedef struct
{
    node *head;
    node *tail;
} Llist;

void **all_pointers = NULL;
int amount_pointers = 0;

void dummy(void) { ; }
void free_all(void);
void free_one(void *ptr);
void check_alloc(void *suspected_pointer);

node *search_node_index(int index, node *head);
node *create_node(char value);
void append_node(node **head, node *new_node);
void insert_node(node *target, node *new_node, node **tail);
void free_lnked_list(node *head);

void get_input(char **hex_1, char **hex_2, char *operator);
Llist hex_string_to_Llist(const char *hex);
void add_hex(node *list_1, node *list_2, Llist *result, int ast_carray);
void sub_hex(node *list_1, node *list_2, Llist *result, int ast_carray);
char *list_to_string(node *head);
int max(int a, int b, int c);
void handle_beginning_0(node **head);

int main(void)
{
    char operator= 0;
    char *hex_1, *hex_2 = NULL;

    get_input(&hex_1, &hex_2, &operator);

    Llist list_1 = hex_string_to_Llist(hex_1);
    Llist list_2 = hex_string_to_Llist(hex_2);
    Llist result;
    result.head = NULL;
    result.tail = NULL;

    switch (operator)
    {
        case '+':
            add_hex(list_1.head, list_2.head, &result, 0);
            break;
        case '-':
            sub_hex(list_1.head, list_2.head, &result, 0);
            break;
        default:
            printf("Missing operator.\n");
    }

    handle_beginning_0(&result.head);

    char *result_s = list_to_string(result.head);

    int line_length = max(strlen(hex_1), strlen(hex_2), strlen(result_s)) + 1;

    char *vertical_form = calloc(4 * (line_length + 1) + 1, sizeof(char));
    check_alloc(vertical_form);

    char *arr_output[3] = {hex_1, hex_2, result_s};

    for (int i = 0; i < 3; i++)
    {
        int count = strlen(arr_output[i]);
        i = (i == 2) ? 3 : i;
        int j = 0;
        for (; j < line_length - count; j++)
        {
            vertical_form[i * (line_length + 1) + j] = (i == 1 && j == 0) ? operator: ' ';
        }
        for (int k = 0; j < line_length; j++, k++)
        {
            int idx = (i == 3) ? 2 : i;
            vertical_form[i * (line_length + 1) + j] = arr_output[idx][k];
        }
        vertical_form[(i + 1) * (line_length + 1) - 1] = '\n';
    }

    for (int i = 0; i < line_length; i++)
    {
        vertical_form[2 * (line_length + 1) + i] = '-';
    }

    vertical_form[3 * (line_length + 1) - 1] = '\n';

    printf("%s", vertical_form);

    free_lnked_list(list_1.head);
    free_lnked_list(list_2.head);
    free_lnked_list(result.head);
    free_one(hex_1);
    free_one(hex_2);
    free_one(vertical_form);
    free_one(result_s);

    if (DEV == true)
    {
        free_all();
    }
    else
    {
        free_one(all_pointers);
    }
    return 0;
}

void get_input(char **hex_1, char **hex_2, char *operator)
{
    scanf("%c\n", operator);

    *hex_1 = calloc(MAX_DIGITS + 1, sizeof(char));
    check_alloc(*hex_1);
    scanf("%s\n", *hex_1);

    *hex_2 = calloc(MAX_DIGITS + 1, sizeof(char));
    check_alloc(*hex_2);
    scanf("%s", *hex_2);
}

Llist hex_string_to_Llist(const char *hex)
{
    node *head = create_node(hex[0]);
    node *tail = head;

    for (int i = 1; i < (int)strlen(hex); i++)
    {
        append_node(&head, create_node(hex[i]));
    }

    Llist list;

    list.head = head;
    list.tail = tail;
    return list;
}

char *list_to_string(node *head)
{
    int len = 0;
    node *trav = head;
    while (trav != NULL)
    {
        len++;
        trav = trav->next;
    }

    char *str = calloc(len + 1, sizeof(char));
    check_alloc(str);

    trav = head;
    int i = 0;
    while (trav != NULL)
    {
        str[i] = trav->digit;
        trav = trav->next;
        i++;
    }
    str[i] = '\0';

    return str;
}

void add_hex(node *list_1, node *list_2, Llist *result, int last_carray)
{
    if (list_1 == NULL && list_2 == NULL)
    {
        if (last_carray == 1)
        {
            append_node(&result->head, create_node('1'));
        }

        return;
    }

    int value1 = (list_1 != NULL) ? strtol(&list_1->digit, NULL, 16) : 0;
    int value2 = (list_2 != NULL) ? strtol(&list_2->digit, NULL, 16) : 0;

    int sum = value1 + value2 + last_carray;
    last_carray = (sum >= 0x10) ? 1 : 0;
    int remainder = sum % 0x10;

    char tmp[2];
    sprintf(tmp, "%x", remainder);

    append_node(&result->head, create_node(tmp[0]));

    node *next1 = (list_1 != NULL) ? list_1->next : list_1;
    node *next2 = (list_2 != NULL) ? list_2->next : list_2;
    add_hex(next1, next2, result, last_carray);
}

void sub_hex(node *list_1, node *list_2, Llist *result, int last_borrow)
{
    if (list_1 == NULL && list_2 == NULL)
    {
        return;
    }

    int value1 = (list_1 != NULL) ? strtol(&list_1->digit, NULL, 16) : 0;
    int value2 = (list_2 != NULL) ? strtol(&list_2->digit, NULL, 16) : 0;

    int diff = value1 - value2 - last_borrow;

    last_borrow = (diff < 0) ? 1 : 0;
    int remainder = (diff < 0) ? diff + 0x10 : diff;

    char tmp[2];
    sprintf(tmp, "%x", remainder);

    append_node(&result->head, create_node(tmp[0]));

    node *next1 = (list_1 != NULL) ? list_1->next : list_1;
    node *next2 = (list_2 != NULL) ? list_2->next : list_2;
    sub_hex(next1, next2, result, last_borrow);
}

void handle_beginning_0(node **head)
{
    if ((*head)->digit != '0' || (*head)->next == NULL)
    {
        return;
    }

    if (*head == NULL)
    {
        printf("List is empty.");
        return;
    }

    node *temp = *head;
    *head = (*head)->next;
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    free_one(temp);

    handle_beginning_0(head);
}

node *create_node(char value)
{
    node *new_node = calloc(1, sizeof(node));
    check_alloc(new_node);

    new_node->digit = value;

    return new_node;
}

void append_node(node **head, node *new_node)
{
    new_node->next = *head;
    *head = new_node;
}

void insert_node(node *target, node *new_node, node **tail)
{
    // If target is the last node, then new_node becomes the new last node
    if (target->next == NULL)
    {
        target->next = new_node;
        new_node->prev = target;
        new_node->next = NULL;
        *tail = new_node;
    }
    // If target is not the last node, insert new_node behind target
    else
    {
        new_node->prev = target;
        new_node->next = target->next;
        target->next->prev = new_node;
        target->next = new_node;
    }
}

node *search_node_index(int index, node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    node *trav = head;
    int i = 0;
    while (trav != NULL && i < index)
    {
        trav = trav->next;
        i++;
    }
    return trav;
}

void free_lnked_list(node *head)
{
    while (head != NULL)
    {
        node *cleaner = head;
        head = head->next;
        free_one(cleaner);
    }
}

int max(int a, int b, int c)
{
    int max = a;

    if (b > max)
    {
        max = b;
    }

    if (c > max)
    {
        max = c;
    }

    return max;
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
