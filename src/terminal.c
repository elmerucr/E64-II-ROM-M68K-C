#include "terminal.h"
#include "kernel.h"

struct terminal *current_terminal;

void terminal_set_current(struct terminal *local)
{
	current_terminal = local;
}

void terminal_init(u8 size_in_tiles_log2, u16 x_pos, u16 y_pos,
		   u16 foreground_color, u16 background_color)
{
	current_terminal->terminal_blit.flags_0 =
		BLIT_TILE_MODE		|
		BLIT_BACKGROUND_ON	|
		BLIT_SIMPLE_COLOR	|
		BLIT_COLOR_PER_TILE_ON;

	current_terminal->terminal_blit.flags_1 = 0x00;

	size_in_tiles_log2 &= 0b01110111;
	current_terminal->terminal_blit.size_in_tiles_log2 = size_in_tiles_log2;

	current_terminal->total_number_of_tiles =
		(0b1 << (size_in_tiles_log2 & 0b111)) *
		(0b1 << ((size_in_tiles_log2 & 0b1110000) >> 4));

	current_terminal->terminal_blit.x = x_pos;
	current_terminal->terminal_blit.y = y_pos;

	current_terminal->terminal_blit.foreground_color = foreground_color;
	current_terminal->terminal_blit.background_color = background_color;

	current_terminal->terminal_blit.pixel_data = (u16 *)character_ram;

	current_terminal->terminal_blit.tile_data =
		malloc(current_terminal->total_number_of_tiles * sizeof(u8));
	current_terminal->terminal_blit.tile_color_data =
		malloc(current_terminal->total_number_of_tiles * sizeof(u16));
	current_terminal->terminal_blit.tile_background_color_data =
		malloc(current_terminal->total_number_of_tiles * sizeof(u16));

	current_terminal->cursor_position = 0;
	current_terminal->cursor_interval = 20; 	// 0.33s (if timer @ 60Hz)
	current_terminal->cursor_countdown = 0;
	current_terminal->cursor_blink = false;
	current_terminal->current_foreground_color = foreground_color;
}

void terminal_clear()
{
	for (size_t i=0; i < (current_terminal->total_number_of_tiles); i++) {
		current_terminal->terminal_blit.tile_data[i] = ' ';
		current_terminal->terminal_blit.tile_color_data[i] =
			current_terminal->terminal_blit.foreground_color;
		current_terminal->terminal_blit.tile_background_color_data[i] =
			current_terminal->terminal_blit.background_color;
	}
}

void terminal_put_symbol(char symbol)
{
	current_terminal->terminal_blit.tile_data[current_terminal->cursor_position] =
		symbol;
	current_terminal->terminal_blit.tile_color_data[current_terminal->cursor_position] =
		current_terminal->current_foreground_color;
	current_terminal->cursor_position++;
	current_terminal->cursor_position &=
		(current_terminal->total_number_of_tiles - 1);
}

void terminal_activate_cursor()
{
	current_terminal->cursor_original_char =
		current_terminal->terminal_blit.tile_data[current_terminal->cursor_position];
	current_terminal->cursor_blink = true;
	current_terminal->cursor_countdown = 0;
}

void terminal_deactivate_cursor()
{
	current_terminal->cursor_blink = false;
	current_terminal->terminal_blit.tile_data[current_terminal->cursor_position] =
		current_terminal->cursor_original_char;
}

void terminal_timer_callback()
{
	if (current_terminal->cursor_blink == true) {
		if (current_terminal->cursor_countdown == 0) {
			current_terminal->terminal_blit.tile_data[current_terminal->cursor_position] ^= 0x80;
			current_terminal->cursor_countdown += current_terminal->cursor_interval;
		}
		current_terminal->cursor_countdown--;
	}
}
