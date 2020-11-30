#include "command.h"
#include "tty.h"

struct command_env command;

void command_init()
{
	tty_puts("\n>");
}

void command_interprete_line(char *line)
{
	if (*line) {
		tty_puts("\n");
		tty_puts(line);
		tty_putchar('\n');
		tty_putchar('>');
	} else {
		tty_puts("\n");
	}
}
