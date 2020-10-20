#include "kernel.h"


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

	unsigned short *border_color = (unsigned short *)VICV_BORDER_COLOR;
	unsigned char *border_size  = (unsigned char *)VICV_BORDER_SIZE;

	*border_size = getal;

	static unsigned int word_value = 0;

elmer:

	for(;;)
	{
		*border_color = word_value;
		word_value++;
	}
}
