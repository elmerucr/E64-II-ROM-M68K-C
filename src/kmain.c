#include "kernel.h"

void kmain()
{
	pokeb(VICV_BORDER_SIZE, 16);

	static uint16_t color = 0;

	for(;;)
	{
		pokew(VICV_BORDER_COLOR, color);
		color++;
	}
}
