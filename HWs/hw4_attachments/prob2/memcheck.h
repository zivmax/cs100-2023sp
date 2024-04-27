#ifndef CS100_MEMCHECK_H
#define CS100_MEMCHECK_H 1

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 1000

struct Record {
  void *ptr;              // address of the allocated memory
  size_t size;            // size of the allocated memory
  int line_no;            // line number, at which a call to malloc or calloc happens
  const char *file_name;  // name of the file, in which the call to malloc or calloc happens
};

struct Record records[MAX_RECORDS];

void *recorded_malloc(size_t size, int line, const char *file) {
  void *ptr = malloc(size);
  if (ptr != NULL) {
    // YOUR CODE HERE
  }
  return ptr;
}

void *recorded_calloc(size_t cnt, size_t each_size, int line, const char *file) {
  void *ptr = calloc(cnt, each_size);
  if (ptr != NULL) {
    // YOUR CODE HERE
  }
  return ptr;
}

void recorded_free(void *ptr, int line, const char *file) {
  // YOUR CODE HERE
}

void check_leak(void) __attribute__((destructor));

void check_leak(void) {
  // YOUR CODE HERE
}

#define malloc(SIZE) recorded_malloc(SIZE, __LINE__, __FILE__)
#define calloc(CNT, EACH_SIZE) recorded_calloc(CNT, EACH_SIZE, __LINE__, __FILE__)
#define free(PTR) recorded_free(PTR, __LINE__, __FILE__)

#endif // CS100_MEMCHECK_H
