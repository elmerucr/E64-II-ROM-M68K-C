#include "mon.h"
#include "tty.h"

void mon_init()
{
	mon_prompt();

	volatile int *test = NULL;
	test += 0xff;


}

void mon_prompt()
{
	tty_puts("\n.");
	tty_reset_start_end_command();
}

void mon_interprete_line(char *line)
{
	if (line) {
		//
	}
}
