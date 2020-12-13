#include "command.h"
#include "tty.h"
#include "string.h"
#include "mon.h"

struct command_env command;

void command_init()
{
	command_prompt();
}

void command_interprete_line(char *line)
{
	char *token0 = strtok(line, " ");

	if (token0) {
		if (strcmp(token0, "about") == 0 ) {
			tty_puts(
				"\n\n"
				"E64-II is a virtual computer system that runs on macOS and\n"
				"linux. It's mainly inspired by the Commodore 64 but implements\n"
				"significant parts of Amiga 500 and Atari ST technology as well.\n"
			);
		} else if (strcmp(token0, "clear") == 0) {
			tty_clear();
		} else if (strcmp(token0, "mon") == 0) {
			tty0.current_mode = C64;
			mon_init();
			tty0.interpreter = &mon_interprete_line;
		} else if (strcmp(token0, "run") == 0) {
		 	tty_putchar('\n');
		 	tty_puts("start program");
		} else if (strcmp(token0, "ver") == 0) {
			tty_puts("\nversion information");
		} else {
			tty_puts("\nerror: unknown command '");
			tty_puts(token0);
			tty_putchar('\'');
		}
	}
	command_prompt();
}

void command_prompt()
{
	tty_puts("\n>");
	tty_reset_start_end_command();
}
