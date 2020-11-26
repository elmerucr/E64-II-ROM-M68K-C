#include "kernel.h"
#include "blitter.h"
#include "vicv.h"
#include "sids.h"
#include "terminal.h"
#include "timer.h"
#include "cia.h"

void move_sections_from_rom_to_kernel_ram();
void update_vector_table();

void move_terminal()
{
	static int dx=1;
	static int dy=1;
	console->terminal_blit.x += dx;
	console->terminal_blit.y += dy;
	if (console->terminal_blit.x == 0 ||
	    console->terminal_blit.x == 256)
		dx = -dx;
	if (console->terminal_blit.y == 16 ||
	    console->terminal_blit.y == 144)
		dy = -dy;
}

void init()
{
	move_sections_from_rom_to_kernel_ram();
	update_vector_table();

	// to enforce an address error exception
	//__asm__ ("movew %d0,0x911");

	character_ram = malloc(256 * 64 * sizeof(u16));
	build_character_ram((u8 *)CHAR_ROM, (u16 *)character_ram);
	blitter_init();

	VICV->horizontal_border_size = 16;
	VICV->horizontal_border_color = C64_BLACK;

	BLITTER->clear_color = C64_BLUE;

	CIA->keyboard_repeat_delay = 50;
	CIA->keyboard_repeat_speed = 5;
	CIA->control_register = 0b00000001;

	struct terminal main_terminal;
	terminal_set_current(&main_terminal);

	terminal_init(
		BLIT_X__32_TILES | BLIT_Y__16_TILES,
		29,
		36,
		C64_LIGHTGREEN,
		0x86a5
	);

	terminal_clear();

	blitter_add_action((u32)&main_terminal.terminal_blit);

	terminal_puts("** E64-II computer system **\n\nready.\n");

	timer_update_handler(TIMER0, terminal_timer_callback);
	timer_turn_on(TIMER0, 3600);

	timer_update_handler(TIMER1, move_terminal);
	timer_turn_on(TIMER1, 3600);

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

void update_vector_table()
{
	update_vector_number(3,  address_error_exception_handler);
	update_vector_number(26, vicv_vblank_exception_handler);		// irq 2
	update_vector_number(28, timer_exception_handler);		// irq 4
}
