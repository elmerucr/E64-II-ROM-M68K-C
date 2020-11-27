#include "kernel.h"

#ifndef BLITTER_H
#define BLITTER_H

#define BLIT_TILE_MODE		0b00000000
#define BLIT_BITMAP_MODE	0b00000001
#define BLIT_BACKGROUND_OFF	0b00000000
#define BLIT_BACKGROUND_ON	0b00000010
#define BLIT_SIMPLE_COLOR	0b00000000
#define BLIT_MULTI_COLOR	0b00000100
#define BLIT_COLOR_PER_TILE_OFF	0b00000000
#define BLIT_COLOR_PER_TILE_ON	0b00001000

#define BLIT_HOR_STRETCHING	0b00000001
#define BLIT_VER_STRETCHING	0b00000100
#define BLIT_HORIZONTAL_FLIP	0b00010000
#define BLIT_VERTICAL_FLIP	0b00100000

#define BLIT_X___1_TILES	0b00000000
#define BLIT_X___2_TILES	0b00000001
#define BLIT_X___4_TILES	0b00000010
#define BLIT_X___8_TILES	0b00000011
#define BLIT_X__16_TILES	0b00000100
#define BLIT_X__32_TILES	0b00000101
#define BLIT_X__64_TILES	0b00000110
#define BLIT_X_128_TILES	0b00000111

#define BLIT_Y___1_TILES	0b00000000
#define BLIT_Y___2_TILES	0b00010000
#define BLIT_Y___4_TILES	0b00100000
#define BLIT_Y___8_TILES	0b00110000
#define BLIT_Y__16_TILES	0b01000000
#define BLIT_Y__32_TILES	0b01010000
#define BLIT_Y__64_TILES	0b01100000
#define BLIT_Y_128_TILES	0b01110000

#define	BLITTER	((volatile struct blitter_ic *) BLITTER_BASE_ADDRESS)

struct __attribute__((packed)) blitter_ic {
	u8	control_register;
	u8	reserved;
	u16	data_register;
	u32	clear_color;
};

struct __attribute__((packed)) blit {
	u8	flags_0;
	u8	flags_1;
	u8	size_in_tiles_log2;
	u8	currently_unused;
	u16	x;
	u16	y;
	u16	foreground_color;
	u16	background_color;
	u16	*pixel_data;
	u8	*tiles;
	u16	*tiles_color;
	u16	*tiles_background_color;
	void	*user_data;
};

void blitter_init();
void blitter_add_action(void *action);

extern void **blitter_list;

#endif
