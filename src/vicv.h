#include <stdint.h>

#ifndef VICV_H
#define VICV_H

#define SURFACE_BLIT_TILE_MODE          0b00000000
#define SURFACE_BLIT_BITMAP_MODE        0b00000001
#define SURFACE_BLIT_BACKGROUND_OFF     0b00000000
#define SURFACE_BLIT_BACKGROUND_ON      0b00000010
#define SURFACE_BLIT_SIMPLE_COLOR       0b00000000
#define SURFACE_BLIT_MULTI_COLOR        0b00000100
#define SURFACE_BLIT_COLOR_PER_TILE_OFF 0b00000000
#define SURFACE_BLIT_COLOR_PER_TILE_ON  0b00010000

#define SURFACE_BLIT_HORIZONTAL_STRETCHING  0b00000001
#define SURFACE_BLIT_VERTICAL_STRETCHING    0b00000100
#define SURFACE_BLIT_HORIZONTAL_FLIP        0b00010000
#define SURFACE_BLIT_VERTICAL_FLIP          0b00100000

#define SURFACE_BLIT_X___1_TILES    0b00000000
#define SURFACE_BLIT_X___2_TILES    0b00000001
#define SURFACE_BLIT_X___4_TILES    0b00000010
#define SURFACE_BLIT_X___8_TILES    0b00000011
#define SURFACE_BLIT_X__16_TILES    0b00000100
#define SURFACE_BLIT_X__32_TILES    0b00000101
#define SURFACE_BLIT_X__64_TILES    0b00000110
#define SURFACE_BLIT_X_128_TILES    0b00000111

#define SURFACE_BLIT_Y___1_TILES    0b00000000
#define SURFACE_BLIT_Y___2_TILES    0b00010000
#define SURFACE_BLIT_Y___4_TILES    0b00100000
#define SURFACE_BLIT_Y___8_TILES    0b00110000
#define SURFACE_BLIT_Y__16_TILES    0b01000000
#define SURFACE_BLIT_Y__32_TILES    0b01010000
#define SURFACE_BLIT_Y__64_TILES    0b01100000
#define SURFACE_BLIT_Y_128_TILES    0b01110000

struct __attribute__((packed)) surface_blit
{
    uint8_t     flags_0;
    uint8_t     flags_1;
    uint8_t     size_in_tiles_log2;
    uint8_t     currently_unused;
    uint16_t    x;
    uint16_t    y;
    uint16_t    foreground_color;
    uint16_t    background_color;
    uint16_t    *pixel_data;                    // 4 bytes in size (pointer), data type is a color
    uint8_t     *tile_data;                     // 4 bytes pointer, to an 8 bit value
    uint16_t    *tile_color_data;               // 4 bytes
    uint16_t    *tile_background_color_data;    // 4 bytes
    void        *user_data;                     // 4 bytes
};

extern void **blitter_list;

void vicv_vblank_exception_handler();
void vicv_init();

#endif
