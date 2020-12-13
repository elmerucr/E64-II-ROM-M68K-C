#include "command.h"
#include "tty.h"

struct command_env command;

void command_init()
{
	command_prompt();
}

void command_interprete_line(char *line)
{
	char *token0 = command_strtok(line, " ");

	if (token0) {
		if (command_strcmp(token0, "about") == 0 ) {
			tty_puts(
				"\n\n"
				"E64-II is a virtual computer system that runs on macOS and\n"
				"linux. It's mainly inspired by the Commodore 64 but implements\n"
				"significant parts of Amiga 500 and Atari ST\n"
				"technology as well."
			);
		} else if (command_strcmp(token0, "clear") == 0) {
			tty_clear();
		} else if (command_strcmp(token0, "run") == 0) {
		 	tty_putchar('\n');
		 	tty_puts("start program");
		} else if (command_strcmp(token0, "ver") == 0) {
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

/*
 * https://gist.github.com/sushlala/3172c37f2947e96977b6a0682ec55a60
 */
bool is_delim(char c, char *delim)
{
	while (*delim != '\0') {
		if (c == *delim)
			return true;
		delim++;
	}
	return false;
}

/*
 * https://gist.github.com/sushlala/3172c37f2947e96977b6a0682ec55a60
 */
char *command_strtok(char *s, char *delim) {
	static char *p; // start of the next search
	if (!s) {
		s = p;
	}
	if (!s) {
		// user is bad user
		return NULL;
	}

	// handle beginning of the string containing delims
	while (1) {
		if (is_delim(*s, delim)) {
			s++;
			continue;
		}
		if (*s == '\0') {
			return NULL; // we've reached the end of the string
		}
		// now, we've hit a regular character. Let's exit the
		// loop, and we'd need to give the caller a string
		// that starts here.
		break;
  	}

	char *ret = s;
	while (1) {
		if (*s == '\0') {
			p = s; // next exec will return NULL
			return ret;
		}
		if (is_delim(*s, delim)) {
			*s = '\0';
			p = s + 1;
			return ret;
		}
		s++;
	}
}

/*
 * https://stackoverflow.com/questions/20004458/optimized-strcmp-implementation
 */
int command_strcmp(const char * str1, const char * str2)
{
	while (*str1 && (*str1 == *str2))
		str1++, str2++;
	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}
