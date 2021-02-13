#ifndef LOX_CHUNK_H
#define LOX_CHUNK_H

#include "common.h"

typedef enum {
	OP_RETURN,
} OpCode;

typedef struct {
	int count;	// number of items
	int capacity;	// current max no of items
	uint8_t *code;
} Chunk;

void init_chunk(Chunk *chunk);
void write_chunk(Chunk *chunk, uint8_t byte);

#endif
