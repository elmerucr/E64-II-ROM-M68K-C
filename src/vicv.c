#include "vicv.h"
#include "kernel.h"

struct surface_blit default_screen =
{
	0b00001000,     // flags 0 - tile mode, simple color, color per tile
	0b00000000,     // flags 1 - no stretching, mirroring etc
	0b01010110,     // height 2^%101 = 32 chars = 256 pixels, width 2^%110 = 64 chars  = 512 pixels
	0b00000000,     // currently unused.... :-)
	0,              // x
	16,             // y
	0xF0A0,         // foreground color
	0xF222,         // background color
    (uint16_t *)0,
    (uint8_t *) 0,
    (uint16_t *)0,
    (uint16_t *)0,
    (void *)13
};

void vicv_init()
{
    default_screen.pixel_data = (uint16_t *)CHAR_RAM;
    default_screen.tile_data = (uint8_t *)malloc(0x800);
    default_screen.tile_color_data = (uint16_t *)malloc(0x800 * sizeof(uint16_t));
}
