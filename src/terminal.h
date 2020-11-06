#ifndef TERMINAL_H
#define TERMINAL_H

#include "vicv.h"
#include <stdint.h>

struct terminal
{
    struct surface_blit terminal_surface;
    uint16_t total_number_of_tiles;
    uint16_t cursor_position;
    uint16_t current_foreground_color;
};

void terminal_init(struct terminal *this_terminal, uint8_t size_in_tiles_log2, uint16_t x_pos, uint16_t y_pos, uint16_t foreground_color);
void terminal_clear(struct terminal *this_terminal);

#endif
