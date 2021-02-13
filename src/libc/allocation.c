#include <stdlib.h>
#include "allocation.h"
#include "kernel.h"

struct block *block_list;

void allocation_init()
{
	block_list = heap_start;
	block_list->size = 0;
	block_list->next = NULL;
}

void *malloc(size_t size)
{
	void *old_heap_end = heap_end;

	size_t final_size = (size & 0b1) ? size + 1 : size;

	heap_end = (void *)((u32)heap_end + final_size);

	return old_heap_end;
}
