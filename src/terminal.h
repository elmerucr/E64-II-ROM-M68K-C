#ifndef TERMINAL_H
#define TERMINAL_H

#include "blitter.h"
#include <stdint.h>

struct terminal {
	struct blit terminal_blit;
	u16 total_number_of_tiles;
	u16 cursor_position;
	u16 current_foreground_color;
};

void terminal_init(struct terminal *local, u8 size_in_tiles_log2, u16 x_pos, u16 y_pos, u16 foreground_color, u16 background_color);
void terminal_clear(struct terminal *local);
void terminal_put_symbol(struct terminal *local, char value);

#endif
