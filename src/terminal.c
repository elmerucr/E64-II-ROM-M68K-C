#include "terminal.h"
#include "kernel.h"

struct terminal *tty0;

void terminal_set_current(struct terminal *local)
{
	tty0 = local;
}

void terminal_init(u8 size_in_tiles_log2, u16 x_pos, u16 y_pos,
		   u16 foreground_color, u16 background_color)
{
	tty0->tty_blit.flags_0 =
		BLIT_TILE_MODE		|
		BLIT_BACKGROUND_ON	|
		BLIT_SIMPLE_COLOR	|
		BLIT_COLOR_PER_TILE_ON;

	tty0->tty_blit.flags_1 = 0x00;

	size_in_tiles_log2 &= 0b01110111;
	tty0->tty_blit.size_in_tiles_log2 = size_in_tiles_log2;

	tty0->columns = (0b1 << (size_in_tiles_log2 & 0b111));
	tty0->number_of_rows = (0b1 << ((size_in_tiles_log2 & 0b1110000) >> 4));

	tty0->number_of_tiles =
		tty0->columns *
		tty0->number_of_rows;

	tty0->tty_blit.x = x_pos;
	tty0->tty_blit.y = y_pos;

	tty0->tty_blit.foreground_color = foreground_color;
	tty0->tty_blit.background_color = background_color;

	tty0->tty_blit.pixel_data = (u16 *)character_ram;

	tty0->tty_blit.tiles =
		malloc(tty0->number_of_tiles * sizeof(u8));
	tty0->tty_blit.tiles_color =
		malloc(tty0->number_of_tiles * sizeof(u16));
	tty0->tty_blit.tiles_background_color =
		malloc(tty0->number_of_tiles * sizeof(u16));

	tty0->cursor_position = 0;
	tty0->cursor_interval = 20; 	// 0.33s (if timer @ 60Hz)
	tty0->cursor_countdown = 0;
	tty0->cursor_blink = false;
	tty0->current_foreground_color = foreground_color;
	tty0->current_background_color = background_color;
}

void terminal_clear()
{
	for (size_t i=0; i < (tty0->number_of_tiles); i++) {
		tty0->tty_blit.tiles[i] = ' ';
		tty0->tty_blit.tiles_color[i] =
			tty0->tty_blit.foreground_color;
		tty0->tty_blit.tiles_background_color[i] =
			tty0->tty_blit.background_color;
	}
}

void terminal_putsymbol(char symbol)
{
	tty0->tty_blit.tiles[tty0->cursor_position] = symbol;
	tty0->tty_blit.tiles_color[tty0->cursor_position] =
		tty0->current_foreground_color;
	tty0->cursor_position++;
	if (tty0->cursor_position >= tty0->number_of_tiles) {
		terminal_add_bottom_line();
		tty0->cursor_position -= tty0->columns;
	}
}

void terminal_putchar(char value)
{
	switch (value) {
	case '\r':
		tty0->cursor_position -=
			tty0->cursor_position %
				tty0->columns;
		break;
	case '\n':
		tty0->cursor_position -=
			tty0->cursor_position %
				tty0->columns;
		if ((tty0->cursor_position / tty0->columns) ==
		    (tty0->number_of_rows - 1)) {
			    terminal_add_bottom_line();
		} else {
			tty0->cursor_position +=
				tty0->columns;
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
	tty0->cursor_original_char =
		tty0->tty_blit.tiles[tty0->cursor_position];
	tty0->cursor_blink = true;
	tty0->cursor_countdown = 0;
}

void terminal_deactivate_cursor()
{
	tty0->cursor_blink = false;
	tty0->tty_blit.tiles[tty0->cursor_position] =
		tty0->cursor_original_char;
}

void terminal_cursor_left()
{
	tty0->cursor_position--;
	if (tty0->cursor_position >= tty0->number_of_tiles)
		tty0->cursor_position++;
}

void terminal_cursor_right()
{
	tty0->cursor_position++;
	if (tty0->cursor_position >= tty0->number_of_tiles) {
		terminal_add_bottom_line();
		tty0->cursor_position -= tty0->columns;
	}
}

void terminal_cursor_up()
{
	tty0->cursor_position -= tty0->columns;
	if (tty0->cursor_position >= tty0->number_of_tiles)
		tty0->cursor_position += tty0->columns;
}

void terminal_cursor_down()
{
	tty0->cursor_position += tty0->columns;
	if (tty0->cursor_position >= tty0->number_of_tiles) {
		terminal_add_bottom_line();
		tty0->cursor_position -= tty0->columns;
	}
}

void terminal_backspace()
{
	u16 pos = tty0->cursor_position;
	if (pos) {
		tty0->cursor_position--;
		while (pos % tty0->columns) {
			tty0->tty_blit.tiles[pos - 1] =
				tty0->tty_blit.tiles[pos];
			tty0->tty_blit.tiles_color[pos - 1] =
				tty0->tty_blit.tiles_color[pos];
			tty0->tty_blit.tiles_background_color[pos - 1] =
				tty0->tty_blit.tiles_background_color[pos];
			pos++;
		}
		tty0->tty_blit.tiles[pos - 1] = ' ';
		tty0->tty_blit.tiles_color[pos - 1] =
			tty0->current_foreground_color;
		tty0->tty_blit.tiles_background_color[pos - 1] =
			tty0->current_background_color;
	}
}

void terminal_timer_callback()
{
	if (tty0->cursor_blink == true) {
		if (tty0->cursor_countdown == 0) {
			tty0->tty_blit.tiles[tty0->cursor_position] ^= 0x80;
			tty0->cursor_countdown += tty0->cursor_interval;
		}
		tty0->cursor_countdown--;
	}
}

void terminal_add_bottom_line()
{
	u8 columns = tty0->columns;

	for (size_t i=0; i<((tty0->number_of_tiles) - columns); i++) {
		tty0->tty_blit.tiles[i] =
			tty0->tty_blit.tiles[i + columns];
		tty0->tty_blit.tiles_color[i] =
			tty0->tty_blit.tiles_color[i + tty0->columns];
		tty0->tty_blit.tiles_background_color[i] =
			tty0->tty_blit.tiles_background_color[i + tty0->columns];
	}
	for (size_t i=tty0->number_of_tiles - tty0->columns; i<tty0->number_of_tiles; i++)
		tty0->tty_blit.tiles[i] = ' ';
}
