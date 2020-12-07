#include "mon.h"
#include "tty.h"

void mon_prompt()
{
	tty_puts("\n.");
	tty_reset_start_end_command();
}
