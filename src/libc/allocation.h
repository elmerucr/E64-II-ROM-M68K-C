#ifndef ALLOCATION_H
#define ALLOCATION_H

#include "kernel.h"

struct block {
	size_t size;		// must be evenly sized
	u16 free;		// 0 = occupied, 1 = free
	struct block *next;
};

void allocation_init();
void allocation_split(struct block *fitting_slot, size_t size);

#endif
