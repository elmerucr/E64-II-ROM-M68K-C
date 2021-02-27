#include <stdio.h>
#include "lox.h"

void lox_init()
{
	printf("\nlox (craftinginterpreters.com)\n");

	Chunk chunk;
	init_chunk(&chunk);
	write_chunk(&chunk, OP_RETURN);
	disassemble_chunk(&chunk, "test_chunk");
	free_chunk(&chunk);
}

void lox_cleanup()
{
	//
}

char *lox_prompt()
{
	return "\n> ";
}

void lox_interprete(char *line)
{
	//
}
