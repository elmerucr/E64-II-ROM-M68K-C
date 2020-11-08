#include "terminal.h"
#include "kernel.h"

void terminal_init(struct terminal *local, u8 size_in_tiles_log2, u16 x_pos,
		   u16 y_pos, u16 foreground_color, u16 background_color)
{
	local->terminal_blit.flags_0 =
		BLIT_TILE_MODE		|
		BLIT_BACKGROUND_ON	|
		BLIT_SIMPLE_COLOR	|
		BLIT_COLOR_PER_TILE_ON;

	local->terminal_blit.flags_1 = 0x00;

	size_in_tiles_log2 &= 0b01110111;
	local->terminal_blit.size_in_tiles_log2 = size_in_tiles_log2;

	local->total_number_of_tiles =
		(0b1 << (size_in_tiles_log2 & 0b111)) * (0b1 << ((size_in_tiles_log2 & 0b1110000) >> 4));

	local->terminal_blit.x = x_pos;
	local->terminal_blit.y = y_pos;

	local->terminal_blit.foreground_color = foreground_color;
	local->terminal_blit.background_color = background_color;

	local->terminal_blit.pixel_data = (u16 *)character_ram;

	local->terminal_blit.tile_data = malloc(local->total_number_of_tiles * sizeof(u8));
	local->terminal_blit.tile_color_data = malloc(local->total_number_of_tiles * sizeof(u16));
	local->terminal_blit.tile_background_color_data = malloc(local->total_number_of_tiles * sizeof(u16));

	local->cursor_position = 0;
	local->current_foreground_color = foreground_color;
}

void terminal_clear(struct terminal *local)
{
	for (size_t i=0; i < (local->total_number_of_tiles); i++) {
		local->terminal_blit.tile_data[i] = ' ';

		local->terminal_blit.tile_color_data[i] =
			local->terminal_blit.foreground_color;

		local->terminal_blit.tile_background_color_data[i] =
			local->terminal_blit.background_color;
	}
}

void terminal_put_symbol(struct terminal *local, char symbol)
{
	local->terminal_blit.tile_data[local->cursor_position] = symbol;
	local->terminal_blit.tile_color_data[local->cursor_position] = local->current_foreground_color;
	local->cursor_position++;
	local->cursor_position &= (local->total_number_of_tiles - 1);
}