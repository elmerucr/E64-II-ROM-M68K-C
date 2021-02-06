#include <stdlib.h>

#include "kernel.h"

void *malloc(size_t size)
{
	void *old_heap_end = heap_end;

	size_t final_size = (size & 0b1) ? size + 1 : size;

	heap_end = (void *)((u32)heap_end + final_size);

	return old_heap_end;
}
