#include "kernel.h"
#include "blitter.h"
#include "vicv.h"
#include "sids.h"
#include "terminal.h"
#include "timer.h"
#include "cia.h"

void move_sections_from_rom_to_kernel_ram();
void update_vector_table();

struct terminal main_terminal;

static void increase_clear_color() { BLITTER->clear_color++; }

void init()
{
	move_sections_from_rom_to_kernel_ram();
	update_vector_table();

	// testing timer
	timer_update_handler(TIMER0, increase_clear_color);
	timer_turn_on(TIMER0, 480);

	// to enforce an address error exception
	//__asm__ ("movew %d0,0x911");

	character_ram = malloc(256 * 64 * sizeof(u16));
	build_character_ram((u8 *)CHAR_ROM, (u16 *)character_ram);
	blitter_init();

	VICV->horizontal_border_size = 16;
	VICV->horizontal_border_color = C64_BLUE;

	BLITTER->clear_color = C64_BLUE;

	CIA->keyboard_repeat_delay = 50;
	CIA->keyboard_repeat_speed = 5;
	CIA->control_register = 0b00000001;

	terminal_init(
		&main_terminal,
		BLIT_X__16_TILES | BLIT_Y___8_TILES,
		128,
		16,
		C64_LIGHTGREEN,
		C64_GREEN
	);

	blitter_add_action((u32)&main_terminal.terminal_blit);

	terminal_clear(&main_terminal);

	terminal_put_symbol(&main_terminal, ' ');
	terminal_put_symbol(&main_terminal, '*');
	terminal_put_symbol(&main_terminal, '*');
	terminal_put_symbol(&main_terminal, ' ');
	terminal_put_symbol(&main_terminal, 'e');
	terminal_put_symbol(&main_terminal, 'l');
	terminal_put_symbol(&main_terminal, 'm');
	terminal_put_symbol(&main_terminal, 'e');
	terminal_put_symbol(&main_terminal, 'r');
	terminal_put_symbol(&main_terminal, 'u');
	terminal_put_symbol(&main_terminal, 'c');
	terminal_put_symbol(&main_terminal, 'r');
	terminal_put_symbol(&main_terminal, ' ');
	terminal_put_symbol(&main_terminal, '*');
	terminal_put_symbol(&main_terminal, '*');

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
