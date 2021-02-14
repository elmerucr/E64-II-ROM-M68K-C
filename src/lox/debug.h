#ifndef LOX_DEBUG_H
#define LOX_DEBUG_H

#include "chunk.h"

void disassemble_chunk(Chunk *chunk, const char *name);
int disassemble_instruction(Chunk *chunk, int offset);

#endif
