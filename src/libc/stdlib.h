#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>
#include <stddef.h>

void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

void exit(int status);

#endif
