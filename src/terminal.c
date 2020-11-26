#include "terminal.h"
#include "kernel.h"

struct terminal *console;

void terminal_set_current(struct terminal *local)
{
	console = local;
}

void terminal_init(u8 size_in_tiles_log2, u16 x_pos, u16 y_pos,
		   u16 foreground_color, u16 background_color)
{
	console->terminal_blit.flags_0 =
		BLIT_TILE_MODE		|
		BLIT_BACKGROUND_ON	|
		BLIT_SIMPLE_COLOR	|
		BLIT_COLOR_PER_TILE_ON;

	console->terminal_blit.flags_1 = 0x00;

	size_in_tiles_log2 &= 0b01110111;
	console->terminal_blit.size_in_tiles_log2 = size_in_tiles_log2;

	console->columns = (0b1 << (size_in_tiles_log2 & 0b111));
	console->number_of_rows = (0b1 << ((size_in_tiles_log2 & 0b1110000) >> 4));

	console->total_number_of_tiles =
		console->columns *
		console->number_of_rows;

	console->terminal_blit.x = x_pos;
	console->terminal_blit.y = y_pos;

	console->terminal_blit.foreground_color = foreground_color;
	console->terminal_blit.background_color = background_color;

	console->terminal_blit.pixel_data = (u16 *)character_ram;

	console->terminal_blit.tile_data =
		malloc(console->total_number_of_tiles * sizeof(u8));
	console->terminal_blit.tile_color_data =
		malloc(console->total_number_of_tiles * sizeof(u16));
	console->terminal_blit.tile_background_color_data =
		malloc(console->total_number_of_tiles * sizeof(u16));

	console->cursor_position = 0;
	console->cursor_interval = 20; 	// 0.33s (if timer @ 60Hz)
	console->cursor_countdown = 0;
	console->cursor_blink = false;
	console->current_foreground_color = foreground_color;
}

void terminal_clear()
{
	for (size_t i=0; i < (console->total_number_of_tiles); i++) {
		console->terminal_blit.tile_data[i] = ' ';
		console->terminal_blit.tile_color_data[i] =
			console->terminal_blit.foreground_color;
		console->terminal_blit.tile_background_color_data[i] =
			console->terminal_blit.background_color;
	}
}

void terminal_putsymbol(char symbol)
{
	console->terminal_blit.tile_data[console->cursor_position] =
		symbol;
	console->terminal_blit.tile_color_data[console->cursor_position] =
		console->current_foreground_color;
	console->cursor_position++;
	console->cursor_position &=
		(console->total_number_of_tiles - 1);
}

void terminal_putchar(char value)
{
	switch (value) {
	case '\r':
		console->cursor_position -=
			console->cursor_position %
				console->columns;
		break;
	case '\n':
		console->cursor_position -=
			console->cursor_position %
				console->columns;
		if ((console->cursor_position / console->columns) ==
		    (console->number_of_rows - 1)) {
			    terminal_add_bottom_line();
		} else {
			console->cursor_position +=
				console->columns;
		}
		break;
	default:
		terminal_putsymbol(value);
		break;
	}
}

void terminal_puts(char *text)
{
	while (*text) {
		terminal_putchar(*text);
		text++;
	}
}

void terminal_activate_cursor()
{
	console->cursor_original_char =
		console->terminal_blit.tile_data[console->cursor_position];
	console->cursor_blink = true;
	console->cursor_countdown = 0;
}

void terminal_deactivate_cursor()
{
	console->cursor_blink = false;
	console->terminal_blit.tile_data[console->cursor_position] =
		console->cursor_original_char;
}

void terminal_cursor_left()
{
	console->cursor_position--;
	console->cursor_position &=
		(console->total_number_of_tiles - 1);
}

void terminal_cursor_right()
{
	console->cursor_position++;
	console->cursor_position &=
		(console->total_number_of_tiles - 1);
}

void terminal_cursor_up()
{
	console->cursor_position -=
		console->columns;
	console->cursor_position &=
		(console->total_number_of_tiles - 1);
}

void terminal_cursor_down()
{
	console->cursor_position +=
		console->columns;
	console->cursor_position &=
		(console->total_number_of_tiles - 1);
}

void terminal_timer_callback()
{
	if (console->cursor_blink == true) {
		if (console->cursor_countdown == 0) {
			console->terminal_blit.tile_data[console->cursor_position] ^= 0x80;
			console->cursor_countdown += console->cursor_interval;
		}
		console->cursor_countdown--;
	}
}

void terminal_add_bottom_line()
{
	u8 columns = console->columns;

	for (size_t i=0; i<((console->total_number_of_tiles) - columns); i++) {
		console->terminal_blit.tile_data[i] =
			console->terminal_blit.tile_data[i + columns];
		console->terminal_blit.tile_color_data[i] =
			console->terminal_blit.tile_color_data[i + console->columns];
		console->terminal_blit.tile_background_color_data[i] =
			console->terminal_blit.tile_background_color_data[i + console->columns];
	}
	for (size_t i=console->total_number_of_tiles - console->columns; i<console->total_number_of_tiles; i++)
		console->terminal_blit.tile_data[i] = ' ';
}
