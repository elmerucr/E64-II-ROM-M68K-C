#include "kernel.h"

unsigned char kpeekb(unsigned char *address)
{
    return *address;
}

void kpokeb(unsigned long address, unsigned char byte)
{
    *(unsigned char *)address = byte;
}

void kpokew(unsigned long address, unsigned int word)
{
    *(unsigned int *)address = word;
}

void kpokel(unsigned long address, unsigned long lwrd)
{
    *(unsigned long *)address = lwrd;
}
