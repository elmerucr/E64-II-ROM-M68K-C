#include "vicv.h"
#include "kernel.h"

#define MAX_BLITS   256

struct surface_blit default_screen =
{
	0b00001000,     // flags 0 - tile mode, simple color, color per tile
	0b00000000,     // flags 1 - no stretching, mirroring etc
	0b01010110,     // height 2^%101 = 32 chars = 256 pixels, width 2^%110 = 64 chars  = 512 pixels
	0b00000000,     // currently unused.... :-)
	0,              // x
	16,             // y
	C64_LIGHTBLUE,  // foreground color
	C64_BLUE,       // background color
    (uint16_t *)0,
    (uint8_t  *)0,
    (uint16_t *)0,
    (uint16_t *)0,
    (void     *)0
};

void **blitter_list;

void vicv_init()
{
    blitter_list = malloc(MAX_BLITS * sizeof(void *));
    for(int i=0; i<MAX_BLITS; i++) blitter_list[i] = (void *)0x00000000;

    blitter_list[0] = (void *)0x80000000;
    blitter_list[1] = (void *)&default_screen;

    default_screen.pixel_data = (uint16_t *)character_ram;
    default_screen.tile_data = (uint8_t *)malloc(0x800);
    default_screen.tile_color_data = (uint16_t *)malloc(0x800 * sizeof(uint16_t));
}
