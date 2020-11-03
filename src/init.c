#include "kernel.h"
#include "vicv.h"
#include "sids.h"

void init()
{
    /*	Move relevant portion of initialized data to ram.
	 *	A few labels have been declared in the rom.ld file.
	 */
	extern char etext, data, edata, bss, bssend;
	char *src = &etext;
	char *dst = &data;

	/*	ROM has .data section at end of .text, copy it to
	 *	the right location.
	 */
	while (dst < &edata) *dst++ = *src++;

	/*	Zero out the .bss section.
	 */
	for (dst = &bss; dst< &bssend; dst++) *dst = 0x00;

	/*	Initialize the heap pointers. heap_end points to
	 *	the currently available memory location.
	 */
	heap_start = (void *)&bssend;
	heap_end   = heap_start;

	update_vector_table(3,  address_error_exception_handler);
	update_vector_table(26, vicv_vblank_exception_handler);		// vector 26 (interrupt level 2) connected to vblank handler

	character_ram = malloc(256 * 64 * sizeof(uint16_t));
	build_character_ram((uint8_t *)CHAR_ROM, (uint16_t *)character_ram);
	vicv_init();
	pokew(VICV_BORDER_COLOR,   C64_BLACK);
	pokew(BLITTER_CLEAR_COLOR, C64_BLUE );

	/*	Enable all interrupts with level 2 and higher.
	 */
	set_interrupt_priority_level(1);

	sids_reset();
	sids_welcome_sound();

    kmain();
}
