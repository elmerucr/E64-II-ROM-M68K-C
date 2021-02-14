#include "lox.h"
#include "tty.h"

void lox_init()
{
	tty_puts("\nlox interpreter");
}

void lox_cleanup()
{
	//
}

char *lox_prompt()
{
	return "\n> ";
}

void lox_interprete_line(char *line)
{
	//
}
