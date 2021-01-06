#include "kernel.h"
#include "vicv.h"
#include "cia.h"

/*
 * Global vars and objects accessible from within kernel
 */
void *heap_start;
void *heap_end;
void *character_ram;
void *user_start;
struct tty tty0;

int update_vector_number(u8 vector_no, void *exception_handler)
{
	if ((vector_no < 2))
		return 0xff;

	/*
	 * The value being written by this function is a void * (address to an
	 * exception handler). This value needs to be written into a memory
	 * location that is calculated based on the vector number which is a
	 * pointer by itself. Hence, the type is void **
	 */
	void **vector_address = (void *)((u32)vector_no << 2);
	disable_interrupts();
	*vector_address = exception_handler;
	restore_interrupts();
	return 0;
}

void *memcpy(u8 *dest, const u8 *src, size_t count)
{
	for (u32 i=0; i<count; i++)
		dest[i] = src[i];
	return dest;
}

u8 *memset(u8 *dest, u8 val, size_t count)
{
	for (u32 i=0; i<count; i++)
		dest[i] = val;
	return dest;
}

void build_character_ram(u8 *source, u16 *dest)
{
	for (int i=0; i<2048; i++) {
		u8 byte = source[i];
		u8 count = 8;
		while (count--) {
			*dest = (byte & 0b10000000) ? C64_GREY : 0x0000;
			dest++;
			byte = byte << 1;
		}
	}
}

// u8 get_interrupt_priority_level()
// {
// 	u16 status_register;

// 	__asm__ __volatile__ (
// 		"movew %%sr,%%d0	\n\t"
// 		"movew %%d0,%0"
// 		: "=g" (status_register)	/* outputs */
// 	);

// 	return (u8)((status_register & 0x0700) >> 8);
// }

void set_interrupt_priority_level(u16 value)
{
	value = (value & 0b00000111) << 8;

	__asm__ __volatile__ (
		"move.w %0,%%d0      \n\t"
		"move.w %%sr,%%d1    \n\t"
		"andi.w #0xf8ff,%%d1 \n\t"
		"or.w %%d0,%%d1      \n\t"
		"move.w %%d1,%%sr    "
		:               /* outputs */
		: "g"(value)    /* inputs  */
		:               /* clobbered regs */
	);
}

void *malloc(size_t n)
{
	void *old_heap_end = heap_end;

	size_t final_n = (n & 0b1) ? n + 1 : n;

	heap_end = (void *)((u32)heap_end + final_n);

	return old_heap_end;
}

void kmain()
{
	tty_activate_cursor();

	for (;;) {
		if (CIA->status_register) {
			tty_deactivate_cursor();
			u8 key_value = CIA->key_next_ascii;
			switch (key_value) {
			case ASCII_CURSOR_LEFT:
				tty_cursor_left();
				break;
			case ASCII_CURSOR_RIGHT:
				tty_cursor_right();
				break;
			case ASCII_CURSOR_UP:
				tty_cursor_up();
				break;
			case ASCII_CURSOR_DOWN:
				tty_cursor_down();
				break;
			case ASCII_BACKSPACE:
				tty_backspace();
				break;
			case ASCII_LF:
				tty_enter_command();
				break;
			default:
				if (!tty_is_command_size_max()) {
					tty_increase_command_size();
					tty_insert();
					tty_putchar(key_value);
				}
				break;
			}
			tty_activate_cursor();
		}
	}
}
