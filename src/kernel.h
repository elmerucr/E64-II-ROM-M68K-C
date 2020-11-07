#include <stdint.h>
#include <stddef.h>
#include "definitions.h"

#ifndef KERNEL_H
#define KERNEL_H

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
// typedef int8_t   i8;
// typedef int16_t  i16;
// typedef int32_t  i32;

void kmain();

// poke & peek functionality
inline void pokeb(u32 address, u8 byte) { *(u8 *)address = byte; }
inline void pokew(u32 address, u16 word) { *(u16 *)address = word; }
inline void pokel(u32 address, u32 lwrd) { *(u32 *)address = lwrd; }
inline u8  peekb(u32 address) { return *(u8 *)address; }
inline u16 peekw(u32 address) { return *(u16 *)address; }
inline u32 peekl(u32 address) { return *(u32 *)address; }

u8 *memcpy(u8 *dest, const u8 *src, size_t count);
u8 *memset(u8 *dest, u8 val, size_t count);

extern void *heap_start;
extern void *heap_end;
extern void *character_ram;

void *malloc(size_t chunk);

void build_character_ram(u8 *source, u16 *dest);
int  update_vector_table(u8 vector_no, void *exception_handler);
void set_interrupt_priority_level(u16 value);
void address_error_exception_handler();

#endif
