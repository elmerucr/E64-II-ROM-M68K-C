#include "blitter.h"
#include "kernel.h"

#define MAX_BLITS   256

struct blit default_screen =
{
	0b00001000,	// flags 0 - tile mode, simple color, color per tile
	0b00000000,	// flags 1 - no stretching, mirroring etc
	0b01010110,	// height 2^%101 = 32 chars (256 pix), width 2^%110 = 64 chars (512 pix)
	0b00000000,	// currently unused.... :-)
	0,		// x
	16,		// y
	C64_LIGHTBLUE,	// foreground color
	C64_BLUE,	// background color
	(u16 *)0,
	(u8  *)0,
	(u16 *)0,
	(u16 *)0,
	(void *)0
};

void **blitter_list;
u8 available;

void blitter_init()
{
	available = 0;
	blitter_list = malloc(MAX_BLITS * sizeof(void *));
	for (int i=0; i<MAX_BLITS; i++)
		blitter_list[i] = (void *)0x00000000;

	blitter_list[0] = (void *)0x80000000;
	blitter_list[1] = (void *)&default_screen;
	available += 2;

	default_screen.pixel_data = (u16 *)character_ram;
	default_screen.tile_data = malloc(0x800);
	default_screen.tile_color_data = malloc(0x800 * sizeof(u16));
	default_screen.tile_background_color_data = malloc(0x800 * sizeof(u16));
}

void blitter_add_action(u32 action)
{
	blitter_list[available] = (void *)action;
	available++;
}
