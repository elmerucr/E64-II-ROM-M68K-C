#include "command.h"
#include "tty.h"

struct command_env command;

void command_init()
{
	command_prompt();
}

void command_interprete_line(char *line)
{
	if (*line) {
		tty_putchar('\n');
		tty_puts(line);
	}
	command_prompt();
}

void command_prompt()
{
	tty_puts("\n>");
	tty_reset_start_end_command();
}
