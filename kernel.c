#include "kernel.h"


void kpokeb(unsigned char *address, unsigned char byte)
{
    *address = byte;
}

void kpokew(unsigned int *address, unsigned int word)
{
    *address = word;
}
