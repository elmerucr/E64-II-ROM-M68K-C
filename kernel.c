#include "kernel.h"

uint8_t kpeekb(uint32_t address)
{
    return *(uint8_t *)address;
}

uint16_t kpeekw(uint32_t address)
{
    return *(uint16_t *)address;
}

uint32_t kpeekl(uint32_t address)
{
    return *(uint32_t *)address;
}

void kpokeb(uint32_t address, uint8_t  byte)
{
    *(uint8_t *)address = byte;
}

void kpokew(uint32_t address, uint16_t word)
{
    *(uint16_t *)address = word;
}

void kpokel(uint32_t address, uint32_t lwrd)
{
    *(uint32_t *)address = lwrd;
}
