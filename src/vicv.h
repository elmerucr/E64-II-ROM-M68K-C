#ifndef VICV_H
#define VICV_H

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
    uint16_t    *pixel_data;                    // should be 4 bytes in size (it's pointer), its data type is a color
    uint8_t     *tile_data;                     // again 4 bytes (check!), to an 8 bit value
    uint16_t    *tile_color_data;               // 4 bytes
    uint16_t    *tile_background_color_data;    // 4 bytes
    void        *user_data;                     // 4 bytes
};

void vblank_exception_handler();

#endif
