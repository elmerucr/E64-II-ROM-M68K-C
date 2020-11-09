#include "kernel.h"
#include "vicv.h"

void kmain()
{
	u16 color = 0;

	for (u32 i=0; i<1000000; i++) {
		VICV->horizontal_border_color = color++;
	}

	VICV->horizontal_border_color = C64_BLACK;

	for (;;) {}
}
