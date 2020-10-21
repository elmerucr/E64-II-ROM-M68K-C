#include "kernel.h"

unsigned char kpeekb(unsigned char *address)
{
    return *address;
}

void kpokeb(unsigned char *address, unsigned char byte)
{
    *address = byte;
}

void kpokew(unsigned int *address, unsigned int word)
{
    *address = word;
}

void kpokel(unsigned long *address, unsigned long lwrd)
{
    *address = lwrd;
}
