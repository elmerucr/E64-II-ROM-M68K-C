#include "kernel.h"
#include "vicv.h"

void init()
{
    // move relevant portion of initialized data to ram
	extern char etext, data, edata, bss, bssend;
	char *src = &etext;
	char *dst = &data;
	// ROM has .data section at end of .text, copy it
	while (dst < &edata) *dst++ = *src++;
	// Zero .bss section
	for (dst = &bss; dst< &bssend; dst++) *dst = 0xb0;


	pokew(BLITTER_CLEAR_COLOR, C64_BLUE);

	update_vector_table(26, vblank_exception_handler);	// vector 26 (interrupt level 2) connected to vblank handler

	set_interrupt_priority_mask(1);

    kmain();
}
