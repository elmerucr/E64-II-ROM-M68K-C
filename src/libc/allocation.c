#include <stdlib.h>
#include <string.h>
#include "allocation.h"
#include "kernel.h"

/*
 * Some ideas have been inspired by:
 * http://tharikasblogs.blogspot.com/p/how-to-write-your-own-malloc-and-free.html
 */

struct block *block_list;

void allocation_init()
{
	block_list = heap_start;

	// set the first block
	block_list->size = (heap_end - heap_start) - sizeof(struct block);
	block_list->free = 1;
	block_list->next = NULL;
}

void allocation_split(struct block *fitting_slot, size_t size)
{
	struct block *new = (void *)((void *)fitting_slot + size + sizeof(struct block));

	new->size = (fitting_slot->size) - size - sizeof(struct block);
	new->free = 1;
	new->next = fitting_slot->next;

	fitting_slot->size = size;
	fitting_slot->free = 0;
	fitting_slot->next = new;
}

// void *malloc(size_t size)
// {
// 	void *old_heap_end = heap_end;

// 	size_t final_size = (size & 0b1) ? size + 1 : size;

// 	heap_end = (void *)((u32)heap_end + final_size);

// 	return old_heap_end;
// }

void *malloc(size_t bytes)
{
	// ensure even amount of bytes
	if (bytes & 0b1) bytes++;

	struct block *curr, *prev;
	void *result;

	curr = block_list;

	while (((curr->size) < bytes) || ((curr->free) == 0) && ((curr->next) != NULL)) {
		prev = curr;
		curr = curr->next;
	}

	if ((curr->size) == bytes) {
		curr->free = 0;
		result = (void *)++curr; // points to memory straight after struct
		// exact fitting of required memory
		return result;
	} else if ((curr->size) > (bytes + sizeof(struct block))) {
		allocation_split(curr, bytes);
		result = (void *)++curr;
		// allocation with a split
		return result;
	} else {
		result = NULL;
		// no memory available from heap
		return result;
	}
}

static void allocation_merge()
{
	struct block *curr, *prev;
	curr = block_list;
	while ((curr->next) != NULL) {
		if ((curr->free) && (curr->next->free)) {
			curr->size += (curr->next->size) + sizeof(struct block);
			curr->next = curr->next->next;
		}
		prev = curr;
		curr = curr->next;
	}
}

void free(void *ptr)
{
	// NEEDS WORK
	// this is a very minimal implementation
	// doesn't iterate through the blocks to check if the given pointer is valid
	if ( (((void *)block_list) <= ptr) && (ptr <= ((void *)END_OF_HEAP))) {
		struct block *curr = ptr;
		--curr;
		curr->free = 1;
		allocation_merge();
	}
}

static size_t allocation_get_size(void *ptr)
{
	struct block *curr = ptr;
	--curr;
	return curr->size;
}

void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL) {
		return malloc(size);
	}

	size_t old_size = allocation_get_size(ptr);

	if (size < old_size)
		return ptr;

	void *new_ptr = malloc(size);

	if (new_ptr == NULL) {
		return NULL;
	}

	memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return new_ptr;
}
