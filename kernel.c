#include "kernel.h"


uint8_t peekb(uint32_t address)
{
    return *(uint8_t *)address;
}


uint16_t peekw(uint32_t address)
{
    return *(uint16_t *)address;
}


uint32_t peekl(uint32_t address)
{
    return *(uint32_t *)address;
}


void pokeb(uint32_t address, uint8_t  byte)
{
    *(uint8_t *)address = byte;
}


void pokew(uint32_t address, uint16_t word)
{
    *(uint16_t *)address = word;
}


void pokel(uint32_t address, uint32_t lwrd)
{
    *(uint32_t *)address = lwrd;
}


uint8_t *memcpy(uint8_t *dest, const uint8_t *src, uint32_t count)
{
    uint32_t i;
    for(i=0; i<count; i++) dest[i] = src[i];
    return dest;
}


uint8_t *memset(uint8_t *dest, uint8_t val, uint32_t count)
{
    uint32_t i;
    for(i=0; i<count; i++) dest[i] = val;
    return dest;
}