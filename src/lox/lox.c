#include "lox.h"
#include "tty.h"

void lox_init()
{
	tty_puts("\nlox (craftinginterpreters.com)");

	Chunk chunk;
	init_chunk(&chunk);
	write_chunk(&chunk, OP_RETURN);
	//disassemble_chunk(&chunk, "test_chunk");
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
