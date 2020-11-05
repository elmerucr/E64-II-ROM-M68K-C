#include "kernel.h"

void kmain()
{
	static uint16_t color = 0;

	for(;;)
	{
		pokew(VICV_BORDER_COLOR, color);
		color++;
	}
}
