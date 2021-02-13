#include "command.h"
#include "tty.h"
#include "string.h"
#include <stdbool.h>
#include "mon.h"
#include "fd.h"

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
		} else if (strcmp(token0, "go") == 0) {
			command_go();
		} else if (strcmp(token0, "mon") == 0) {
			tty0.current_mode = C64;
			mon_init();
			tty0.interpreter = &mon_interprete_line;
		} else if (strcmp(token0, "run") == 0) {
		 	tty_putchar('\n');
		 	tty_puts("start program");
		} else if (strcmp(token0, "ver") == 0) {
			tty_puts("\nversion information");
		} else if (strcmp(token0, "dir") == 0) {
			for (int i=0; i<2880; i++) {
				// NEEDS WORK
				read_sector(i, 0x8a38);
				read_sector(0x13,0x8a38);
			}
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

void command_go()
{
	char *address_string = strtok(NULL, " ");
	if (address_string) {
		u32 address;
		if (hex_string_to_int(address_string, &address)) {
			address &= 0x00ffffff;
			char interpret[7];
			sprint_address_hex(interpret, address);
			if (address & 0b1) {
				tty_printf("\nerror: odd address $%s", interpret);
			} else {
				tty_printf("\njumping to user mode at $%s", interpret);
			}
		} else {
			tty_printf("\nerror: '%s' is not a hex value", address_string);
		}
	} else {
		tty_puts("\nerror: missing address");
	}
}

bool hex_string_to_int(const char *temp_string, u32 *return_value)
{
	u32 val = 0;
	while (*temp_string) {
        	// get current character then increment
        	u8 byte = *temp_string++;
        	// transform hex char to the 4bit equiv. number, using ascii table index
        	if (byte >= '0' && byte <= '9') {
        		byte = byte - '0';
        	} else if (byte >= 'a' && byte <='f') {
        		byte = byte - 'a' + 10;
        	} else if (byte >= 'A' && byte <='F') {
			byte = byte - 'A' + 10;
		} else {
			// problem, return false and do not write the return value
			return false;
        	}
        	// shift 4 to make space for new digit, add 4 bits of the new digit
        	val = (val << 4) | (byte & 0xf);
	}
	*return_value = val;
	return true;
}
