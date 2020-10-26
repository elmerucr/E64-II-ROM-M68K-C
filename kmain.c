#include "kernel.h"

void kmain()
{
	static unsigned char getal = 55;
	getal += 13;

	//uint8_t *border_size  = (uint8_t *)VICV_BORDER_SIZE;

	//*border_size = getal;

	pokeb(VICV_BORDER_SIZE, getal);

	static uint16_t color = 0;

	pokeb(53280, 14);

	for(;;)
	{
		pokew(VICV_BORDER_COLOR, color);
		color++;
	}
}
