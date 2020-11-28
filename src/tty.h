#ifndef TTY_H
#define TTY_H

#include "blitter.h"
#include <stdint.h>
#include <stdbool.h>

struct tty {
	struct blit screen_blit;
	u8  columns;
	u8  number_of_rows;
	u16 number_of_tiles;

	u16	cursor_position;
	u8	cursor_interval;
	u8	cursor_countdown;
	char	cursor_original_char;
	u16	cursor_original_color;
	bool	cursor_blink;		// current state

	u16 current_foreground_color;
	u16 current_background_color;

	char	*command_buffer;
};

void tty_set_current(struct tty *local);

void tty_init(u8 size_in_tiles_log2, u16 x_pos, u16 y_pos,
	      u16 foreground_color, u16 background_color);

void tty_clear();

void tty_putsymbol(char symbol);
void tty_putchar(char value);
void tty_puts(char *text);

void tty_activate_cursor();
void tty_deactivate_cursor();

void tty_cursor_left();
void tty_cursor_right();
void tty_cursor_up();
void tty_cursor_down();
void tty_backspace();
void tty_enter();

void tty_add_bottom_line();

void tty_timer_callback();

#endif
