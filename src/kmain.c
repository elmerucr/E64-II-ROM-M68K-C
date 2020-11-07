#include "kernel.h"

void kmain()
{
	static u16 color = 0;

	for (;;) {
		pokew(VICV_BORDER_COLOR, color);
		color++;
	}
}
