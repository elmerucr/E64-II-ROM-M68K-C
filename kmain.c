#include "kernel.h"
#include <stdint.h>

void kmain(void)
{
	// move relevant portion of initialized data to ram
	extern char etext, data, edata, bss, bssend;
	char *src = &etext;
	char *dst = &data;
	// ROM has .data section at end of .text, copy it
	while (dst < &edata) *dst++ = *src++;
	// Zero .bss section
	for (dst = &bss; dst< &bssend; dst++) *dst = 0xb0;


	static unsigned char getal = 55;
	getal += 13;

	uint8_t *border_size  = (uint8_t *)VICV_BORDER_SIZE;

	*border_size = getal;

	static uint16_t color = 0;

	kpokeb(53280, 14);

	for(;;)
	{
		kpokew(VICV_BORDER_COLOR, color);
		color++;
	}
}
