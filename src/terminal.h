#ifndef TERMINAL_H
#define TERMINAL_H

#include "blitter.h"
#include <stdint.h>
#include <stdbool.h>

struct terminal {
	struct blit terminal_blit;
	u16 total_number_of_tiles;

	u16	cursor_position;
	u8	cursor_interval;
	u8	cursor_countdown;
	char	cursor_original_char;
	u16	cursor_original_color;
	bool	cursor_blink;		// current state

	u16 current_foreground_color;
};

void terminal_set_current(struct terminal *local);

void terminal_init(u8 size_in_tiles_log2, u16 x_pos, u16 y_pos,
		   u16 foreground_color, u16 background_color);

void terminal_clear();

void terminal_put_symbol(char value);

void terminal_activate_cursor();
void terminal_deactivate_cursor();

void terminal_timer_callback();

#endif
