// memcheck.h

#ifndef CS100_MEMCHECK_H
#define CS100_MEMCHECK_H 1

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool DEV = true;


typedef struct
{
    void *ptr;
    size_t size;
    int line;
    const char *file_name;
} record;


record **all_records = NULL;
int amount_records = 0;


record *create_record(void *ptr, size_t size, const char *file, int line)
{
    record *new_record = (record *) malloc(sizeof(record));
    new_record->ptr = ptr;
    new_record->size = size;
    new_record->line = line;
    new_record->file_name = file;

    return new_record;
}


void _free_recorded(void *ptr, const char *file, int line)
{
    if (ptr == NULL)
    {
        return;
    }

    for (int i = 0; i < amount_records; i++)
    {
        if (all_records[i]->ptr == ptr)
        {
            free(ptr);
            all_records[i]->ptr = NULL;
            return;
        }
    }

    printf("Invalid free in file %s, line %d\n", file, line);
}


void _check_alloc(void *suspected_pointer, size_t size_of_alloc, const char *file, int line)
{
    all_records = (record **) realloc(all_records, (amount_records + 1) * sizeof(void *));
    if (all_records == NULL)
    {
        printf("Memory allocation failed in file %s, line %d\n", __FILE__, __LINE__);
    }
    all_records[amount_records] = create_record(suspected_pointer, size_of_alloc, file, line);
    amount_records++;
}


void *_malloc_checked(size_t alloc_size, const char *file, int line)
{
    if ((int) alloc_size >= 0)
    {
        void *new_pointer = malloc(alloc_size);
        _check_alloc(new_pointer, alloc_size, file, line);

        return new_pointer;
    }
    else
    {
        printf("Invalid size for malloc().");
    }

    return NULL;
}


void *_calloc_checked(size_t number, size_t type_size, const char *file, int line)
{
    size_t alloc_size = (int) number * (int) type_size;
    if ((int) alloc_size >= 0)
    {
        void *new_pointer = calloc(number, type_size);
        _check_alloc(new_pointer, alloc_size, file, line);

        return new_pointer;
    }
    else
    {
        printf("Invalid size for calloc().");
    }

    return NULL;
}


void *_realloc_checked(void *old_pointer, size_t size, const char *file, int line)
{
    if ((int) size < 0)
    {
        printf("Invalid size for realloc().");
    }


    int idx = -1;
    if (old_pointer != NULL)
    {
        for (int i = 0; i < amount_records; i++)
        {
            if (all_records[i] == old_pointer)
            {
                all_records[i] = NULL;
                idx = i;
            }
        }
    }

    if (idx != -1)
    {
        void *new_pointer = realloc(old_pointer, size);
        all_records[idx] = create_record(new_pointer, size, file, line);

        return new_pointer;
    }
    else if (old_pointer == NULL)
    {
        void *new_pointer = _malloc_checked(size, file, line);

        return new_pointer;
    }
    else
    {
        printf("Try to realloc() a illegal pointer.");
    }

    return NULL;
}


void check_memory_leaks(void) __attribute__((destructor));

void check_memory_leaks(void)
{
    printf("Summary:\n");

    int count = 0;
    size_t total_leaks = 0;
    for (int i = 0; i < amount_records; i++)
    {
        if (all_records[i]->ptr != NULL)
        {
            count++;
            total_leaks += all_records[i]->size;
            printf("%lu bytes memory not freed (allocated in file %s, line %d)\n",
                   all_records[i]->size, all_records[i]->file_name, all_records[i]->line);

            free(all_records[i]->ptr);
        }

        free(all_records[i]);
    }


    if (count == 0)
    {
        printf("All allocations have been freed.\n");
    }
    else
    {
        printf("%d allocation records not freed (%lu bytes in total).\n", count, total_leaks);
    }

    free(all_records);
}


#define malloc(SIZE) _malloc_checked(SIZE, __FILE__, __LINE__)
#define calloc(CNT, EACH_SIZE) _calloc_checked(CNT, EACH_SIZE, __FILE__, __LINE__)
#define realloc(PTR, SIZE) _realloc_checked(PTR, SIZE, __FILE__, __LINE__)
#define free(ptr) _free_recorded(ptr, __FILE__, __LINE__)

#endif // CS100_MEMCHECK_H
