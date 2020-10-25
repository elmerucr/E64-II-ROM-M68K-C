#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include "kernel_constants.h"

void kinit();
void kmain();

// poke & peek functionality
void kpokeb(uint32_t address, uint8_t  byte);
void kpokew(uint32_t address, uint16_t word);
void kpokel(uint32_t address, uint32_t lwrd);
uint8_t  kpeekb(uint32_t address);
uint16_t kpeekw(uint32_t address);
uint32_t kpeekl(uint32_t address);

#endif
