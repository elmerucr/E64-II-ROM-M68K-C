#ifndef VICV_H
#define VICV_H

#include "kernel.h"

#define	VICV	((volatile struct vicv_ic *) VICV_BASE_ADDRESS)

struct __attribute__((packed)) vicv_ic {
	u8  interrupt_status;
	u8  buffer_swap;
	u8  horizontal_border_size;
	u8  vertical_border_size;
	u16 horizontal_border_color;
	u16 vertical_border_color;
};

void vicv_vblank_exception_handler();

#endif
