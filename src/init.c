#include "kernel.h"
#include "blitter.h"
#include "vicv.h"
#include "sids.h"
#include "terminal.h"

void move_sections_from_rom_to_kernel_ram();

void init()
{
	move_sections_from_rom_to_kernel_ram();

	update_vector_table(3,  address_error_exception_handler);
	update_vector_table(26, vicv_vblank_exception_handler);		// vector 26 (interrupt level 2) connected to vblank handler

	character_ram = malloc(256 * 64 * sizeof(u16));
	build_character_ram((u8 *)CHAR_ROM, (u16 *)character_ram);
	blitter_init();
	pokeb(VICV_BORDER_SIZE, 16);
	pokew(VICV_BORDER_COLOR,   C64_BLACK);
	pokew(BLITTER_CLEAR_COLOR, C64_BLUE );

	struct terminal main_terminal;
	terminal_init(&main_terminal, SURFACE_BLIT_X__64_TILES | SURFACE_BLIT_Y__32_TILES, 0, 16, C64_LIGHTBLUE);

	/*
	 * Enable all interrupts with level 2 and higher.
	 */
	set_interrupt_priority_level(1);

	sids_reset();
	sids_welcome_sound();

    kmain();
}

void move_sections_from_rom_to_kernel_ram()
{
	/*
	 * Move relevant portion of initialized data to ram.
	 * A few labels have been declared in the rom.ld file.
	 */
	extern char etext, data, edata, bss, bssend;
	char *src = &etext;
	char *dst = &data;

	/*
	 * ROM has .data section at end of .text, copy it to the right location
	 */
	while (dst < &edata) *dst++ = *src++;

	/*
	 * zero out the .bss section
	 */
	for (dst = &bss; dst< &bssend; dst++) *dst = 0x00;

	/*
	 * Initialize the heap pointers. heap_end points to the currently
	 * available memory location.
	 */
	heap_start = (void *)&bssend;
	heap_end   = heap_start;
}
