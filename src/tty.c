#include "tty.h"
#include "kernel.h"
#include "cia.h"

struct tty *tty_current;

void tty_set_current(struct tty *local)
{
	tty_current = local;
}

void tty_init(u8 size_in_tiles_log2, u16 x_pos, u16 y_pos,
		   u16 foreground_color, u16 background_color)
{
	tty_current->screen_blit.flags_0 =
		BLIT_TILE_MODE		|
		BLIT_BACKGROUND_ON	|
		BLIT_SIMPLE_COLOR	|
		BLIT_COLOR_PER_TILE_ON;

	tty_current->screen_blit.flags_1 = 0x00;

	size_in_tiles_log2 &= 0b01110111;
	tty_current->screen_blit.size_in_tiles_log2 = size_in_tiles_log2;

	tty_current->columns = (0b1 << (size_in_tiles_log2 & 0b111));
	tty_current->number_of_rows =
		(0b1 << ((size_in_tiles_log2 & 0b1110000) >> 4));

	tty_current->command_buffer =
		malloc(256 * sizeof(char));

	tty_current->number_of_tiles =
		tty_current->columns *
		tty_current->number_of_rows;

	tty_current->screen_blit.x = x_pos;
	tty_current->screen_blit.y = y_pos;

	tty_current->screen_blit.foreground_color = foreground_color;
	tty_current->screen_blit.background_color = background_color;

	tty_current->screen_blit.pixel_data = (u16 *)character_ram;

	tty_current->screen_blit.tiles =
		malloc(tty_current->number_of_tiles * sizeof(u8));
	tty_current->screen_blit.tiles_color =
		malloc(tty_current->number_of_tiles * sizeof(u16));
	tty_current->screen_blit.tiles_background_color =
		malloc(tty_current->number_of_tiles * sizeof(u16));

	tty_current->cursor_position = 0;
	tty_current->cursor_interval = 20; 	// 0.33s (if timer @ 60Hz)
	tty_current->cursor_countdown = 0;
	tty_current->cursor_blink = false;
	tty_current->current_foreground_color = foreground_color;
	tty_current->current_background_color = background_color;
}

void tty_clear()
{
	for (size_t i=0; i < (tty_current->number_of_tiles); i++) {
		tty_current->screen_blit.tiles[i] = ' ';
		tty_current->screen_blit.tiles_color[i] =
			tty_current->screen_blit.foreground_color;
		tty_current->screen_blit.tiles_background_color[i] =
			tty_current->screen_blit.background_color;
	}
	tty_current->cursor_position = 0;
	tty_current->cursor_start_of_command = 0;
	tty_current->cursor_end_of_command = 0;
}

void tty_putsymbol(char symbol)
{
	tty_current->screen_blit.tiles[tty_current->cursor_position] = symbol;
	tty_current->screen_blit.tiles_color[tty_current->cursor_position] =
		tty_current->current_foreground_color;
	tty_current->cursor_position++;
	if (tty_current->cursor_position >= tty_current->number_of_tiles) {
		tty_add_bottom_line();
		tty_current->cursor_position -= tty_current->columns;
	}
}

void tty_putchar(char value)
{
	switch (value) {
	case '\r':
		tty_current->cursor_position -=
			tty_current->cursor_position %
				tty_current->columns;
		break;
	case '\n':
		tty_current->cursor_position -=
			tty_current->cursor_position %
				tty_current->columns;
		if ((tty_current->cursor_position / tty_current->columns) ==
		    (tty_current->number_of_rows - 1)) {
			    tty_add_bottom_line();
		} else {
			tty_current->cursor_position +=
				tty_current->columns;
		}
		break;
	default:
		tty_putsymbol(value);
		tty_current->cursor_end_of_command++;
		break;
	}
}

void tty_puts(char *text)
{
	while (*text) {
		tty_putchar(*text);
		text++;
	}
}

void tty_activate_cursor()
{
	tty_current->cursor_original_char =
		tty_current->screen_blit.tiles[tty_current->cursor_position];
	tty_current->cursor_blink = true;
	tty_current->cursor_countdown = 0;
}

void tty_deactivate_cursor()
{
	tty_current->cursor_blink = false;
	tty_current->screen_blit.tiles[tty_current->cursor_position] =
		tty_current->cursor_original_char;
}

void tty_cursor_left()
{
	u16 min_pos = 0;
	if (tty_current->current_mode == SHELL)
		min_pos = tty_current->cursor_start_of_command;
	if (tty_current->cursor_position > min_pos)
		tty_current->cursor_position--;
}

void tty_cursor_right()
{
	tty_current->cursor_position++;
	switch (tty_current->current_mode) {
	case C64:
		if (tty_current->cursor_position > (tty_current->number_of_tiles - 1)) {
			tty_add_bottom_line();
			tty_current->cursor_position -= tty_current->columns;
		}
		break;
	case SHELL:
		if (tty_current->cursor_position > tty_current->cursor_end_of_command)
			tty_current->cursor_position--;
		break;
	}
}

void tty_cursor_up()
{
	switch (tty_current->current_mode) {
	case C64:
		tty_current->cursor_position -= tty_current->columns;
		if (tty_current->cursor_position >= tty_current->number_of_tiles)
			tty_current->cursor_position += tty_current->columns;
		break;
	case SHELL:
		// NEEDS WORK: show former command
		break;
	}
}

void tty_cursor_down()
{
	switch (tty_current->current_mode) {
	case C64:
		tty_current->cursor_position += tty_current->columns;
		if (tty_current->cursor_position >= tty_current->number_of_tiles) {
			tty_add_bottom_line();
			tty_current->cursor_position -= tty_current->columns;
		}
		break;
	case SHELL:
		// NEEDS WORK: scroll through former commands list
		break;
	}
}

void tty_backspace()
{
	u16 pos = tty_current->cursor_position;
	u16 min_pos = 0;
	if (tty_current->current_mode == SHELL)
		min_pos = tty_current->cursor_start_of_command;
	if (pos > min_pos) {
		tty_current->cursor_position--;
		while (pos % tty_current->columns) {
			tty_current->screen_blit.tiles[pos - 1] =
				tty_current->screen_blit.tiles[pos];
			tty_current->screen_blit.tiles_color[pos - 1] =
				tty_current->screen_blit.tiles_color[pos];
			tty_current->screen_blit.tiles_background_color[pos - 1] =
				tty_current->screen_blit.tiles_background_color[pos];
			pos++;
		}
		tty_current->screen_blit.tiles[pos - 1] = ' ';
		tty_current->screen_blit.tiles_color[pos - 1] =
			tty_current->current_foreground_color;
		tty_current->screen_blit.tiles_background_color[pos - 1] =
			tty_current->current_background_color;
	}
}

void tty_timer_callback()
{
	if (tty_current->cursor_blink == true) {
		if (tty_current->cursor_countdown == 0) {
			tty_current->screen_blit.tiles[tty_current->cursor_position] ^= 0x80;
			tty_current->cursor_countdown += tty_current->cursor_interval;
		}
		tty_current->cursor_countdown--;
	}
}

void tty_add_bottom_line()
{
	u8 columns = tty_current->columns;
	u16 total_tiles = tty_current->number_of_tiles;
	u16 no_of_tiles_to_move = total_tiles - columns;

	for (size_t i=0; i < no_of_tiles_to_move; i++) {
		tty_current->screen_blit.tiles[i] =
			tty_current->screen_blit.tiles[i + columns];
		tty_current->screen_blit.tiles_color[i] =
			tty_current->screen_blit.tiles_color[i + columns];
		tty_current->screen_blit.tiles_background_color[i] =
			tty_current->screen_blit.tiles_background_color[i + columns];
	}
	for (size_t i=no_of_tiles_to_move; i<total_tiles; i++)
		tty_current->screen_blit.tiles[i] = ' ';
	tty_current->cursor_start_of_command -= tty_current->columns;
	tty_current->cursor_end_of_command -= tty_current->columns;
}

void tty_enter()
{
	switch (tty_current->current_mode) {
	case C64:
		{
		u16 start_of_line = tty_current->cursor_position -
			(tty_current->cursor_position % tty_current->columns);
		for (size_t i = 0; i < tty_current->columns; i++) {
			tty_current->command_buffer[i] =
				tty_current->screen_blit.tiles[start_of_line + i];
		}

		size_t i = tty_current->columns - 1;
		while (tty_current->command_buffer[i] == ' ')
			i--;
		tty_current->command_buffer[i + 1] = 0;
		}
		break;
	case SHELL:
		{
		size_t i;
		for (i=tty_current->cursor_start_of_command;
		    i<tty_current->cursor_end_of_command; i++) {
			tty_current->command_buffer[i - tty_current->cursor_start_of_command] =
				tty_current->screen_blit.tiles[i];
		}
		tty_current->command_buffer[i - tty_current->cursor_start_of_command] = 0;
		}
		break;
	}

	tty_current->interpreter(tty_current->command_buffer);
}

void tty_reset_start_end_command()
{
	tty_current->cursor_start_of_command =
		tty_current->cursor_position;
	tty_current->cursor_end_of_command =
		tty_current->cursor_position;
}
