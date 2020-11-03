#include "kernel.h"
#include "vicv.h"


void *heap_start;
void *heap_end;
void *character_ram;


int update_vector_table(uint8_t vector_no, void *exception_handler)
{
    if( (vector_no < 2) ) return 0xff;

    // the value being written by this function is a void * (address to an exception handler)
    // this value needs to be written into a memory location that is
    // calculated based on the vector number which is a pointer by itself
    // hence, the type is void **
    void **vector_address = (void *)((uint32_t)vector_no << 2);

    *vector_address = exception_handler;

    return 0;
}


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


uint8_t *memcpy(uint8_t *dest, const uint8_t *src, size_t count)
{
    for(uint32_t i=0; i<count; i++) dest[i] = src[i];
    return dest;
}


uint8_t *memset(uint8_t *dest, uint8_t val, size_t count)
{
    for(uint32_t i=0; i<count; i++) dest[i] = val;
    return dest;
}


void build_character_ram(uint8_t *source, uint16_t *dest)
{
    for(int i=0; i<2048; i++)
    {
        uint8_t byte = source[i];
        uint8_t count = 8;
        while(count--)
        {
            *dest = (byte & 0b10000000) ? C64_GREY : 0x0000;
            dest++;
            byte = byte << 1;
        }
    }
}


void set_interrupt_priority_level(uint16_t value)
{
    value = (value & 0b00000111) << 8;

    __asm__ __volatile__
    (
        "move.w %0,%%d0      \n\t"
        "move.w %%sr,%%d1    \n\t"
        "andi.w #0xf8ff,%%d1 \n\t"
        "or.w %%d0,%%d1      \n\t"
        "move.w %%d1,%%sr    "
        :               /* outputs */
        : "g"(value)    /* inputs  */
        :               /* clobbered regs */
    );
}

void *malloc(size_t chunk)
{
    void *return_value = heap_end;
    size_t no_of_bytes = (chunk & 0b1) ? chunk+1 : chunk;
    heap_end = (void *)((uint32_t)heap_end + no_of_bytes);
    return return_value;
}