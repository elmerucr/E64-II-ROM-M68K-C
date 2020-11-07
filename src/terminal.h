#ifndef TERMINAL_H
#define TERMINAL_H

#include "blitter.h"
#include <stdint.h>

struct terminal {
	struct surface_blit terminal_surface;
	u16 total_number_of_tiles;
	u16 cursor_position;
	u16 current_foreground_color;
};

void terminal_init(struct terminal *this_terminal, u8 size_in_tiles_log2, u16 x_pos, u16 y_pos, u16 foreground_color);
void terminal_clear(struct terminal *this_terminal);

#endif
