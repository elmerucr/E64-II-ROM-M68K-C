#ifndef TTY_H
#define TTY_H

#include "blitter.h"
#include <stdint.h>
#include <stdbool.h>

enum mode {
	SHELL,
	C64
};

struct tty {
	struct blit screen_blit;
	u8  columns;
	u16 number_of_rows;
	u16 number_of_tiles;

	u16	cursor_position;
	u16	cursor_start_of_command;
	u16	cursor_end_of_command;

	u8	cursor_interval;
	u8	cursor_countdown;
	char	cursor_original_char;
	u16	cursor_original_color;
	bool	cursor_blink;		// current state

	u16 current_foreground_color;
	u16 current_background_color;

	char	*command_buffer;

	enum mode current_mode;

	void	(*interpreter)(char *line);
};

void tty_set_current(struct tty *local);

void tty_init(u8 size_in_tiles_log2, u16 x_pos, u16 y_pos,
	      u16 foreground_color, u16 background_color);

void tty_clear();
void tty_reset_start_end_command();

void tty_putsymbol(char symbol);
void tty_putchar(char value);
int tty_puts(char *text);
int tty_printf(const char *format, ...);

void tty_activate_cursor();
void tty_deactivate_cursor();

void tty_cursor_left();
void tty_cursor_right();
void tty_cursor_up();
void tty_cursor_down();
void tty_backspace();
void tty_insert();
void tty_enter_command();

void tty_increase_command_size();
void tty_decrease_command_size();
int tty_is_command_size_max();

void tty_add_bottom_line();

void tty_timer_callback();

void sprint_byte_hex(char *string, u8 u);
void sprint_word_hex(char *string, u16 u);
void sprint_address_hex(char *string, u32 u);
void sprint_long_hex(char *string, u32 u);

#endif
