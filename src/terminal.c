#include "terminal.h"
#include "definitions.h"
#include "kernel.h"

void terminal_init(struct terminal *this_terminal, uint8_t size_in_tiles_log2, uint16_t x_pos, uint16_t y_pos, uint16_t foreground_color)
{
    this_terminal->terminal_surface.flags_0 =   SURFACE_BLIT_TILE_MODE |
                                                SURFACE_BLIT_BACKGROUND_OFF |
                                                SURFACE_BLIT_SIMPLE_COLOR |
                                                SURFACE_BLIT_COLOR_PER_TILE_ON;

    this_terminal->terminal_surface.flags_1 =   0x00;

    size_in_tiles_log2 &= 0b01110111;
    this_terminal->terminal_surface.size_in_tiles_log2 = size_in_tiles_log2;

    this_terminal->total_number_of_tiles = (0b1 << (size_in_tiles_log2 & 0b111)) * (0b1 << ((size_in_tiles_log2 & 0b1110000) >> 4));

    this_terminal->terminal_surface.x = x_pos;
    this_terminal->terminal_surface.y = y_pos;

    this_terminal->terminal_surface.foreground_color = C64_LIGHTBLUE;
    this_terminal->terminal_surface.background_color = C64_BLUE;

    this_terminal->terminal_surface.pixel_data = (uint16_t *)character_ram;

    this_terminal->terminal_surface.tile_data = (uint8_t *)malloc(this_terminal->total_number_of_tiles * sizeof(uint8_t));
    this_terminal->terminal_surface.tile_color_data = (uint16_t *)malloc(this_terminal->total_number_of_tiles * sizeof(uint16_t));
    this_terminal->terminal_surface.tile_background_color_data = (uint16_t *)malloc(this_terminal->total_number_of_tiles * sizeof(uint16_t));

    this_terminal->cursor_position = 0;
    this_terminal->current_foreground_color = foreground_color;
}

void terminal_clear(struct terminal *this_terminal)
{
    for(size_t i=0; i < (this_terminal->total_number_of_tiles); i++)
    {
        this_terminal->terminal_surface.tile_data[i] = ' ';
        this_terminal->terminal_surface.tile_color_data[i] = this_terminal->current_foreground_color;
    }
}
