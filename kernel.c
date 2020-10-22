#include "kernel.h"

unsigned char kpeekb(unsigned long address)
{
    return *(unsigned char *)address;
}

unsigned int kpeekw(unsigned long address)
{
    return *(unsigned int *)address;
}

unsigned long kpeekl(unsigned long address)
{
    return *(unsigned long *)address;
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
