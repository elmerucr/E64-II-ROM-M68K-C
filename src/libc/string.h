#ifndef STRING_H
#define STRING_H

#include <stddef.h>

void *memcpy(void *, const void *, size_t);
void *memset(void *, int, size_t);
size_t strlen(const char *);
char *strchr(const char *s, int c);
int strcmp(const char *s1, const char *s2);
char *strtok(char *s, char *delim);

#endif
