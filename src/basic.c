#include "basic.h"
#include "tty.h"

struct basic_env basic;

void basic_cold_start()
{
	basic.start_of_text = malloc(65535);
	basic.start_of_vars = malloc(65536);
	basic.end_of_text = basic.start_of_vars;
	basic.end_of_vars = basic.start_of_vars + 65536;
}

void basic_interprete_line(char *line)
{
	if (*line) {
		tty_putchar('\n');
		tty_puts(line);
		tty_puts("<<END>>");
	}
	tty_puts("\n");
}
