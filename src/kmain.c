#include "kernel.h"
#include "vicv.h"
#include "cia.h"

void kmain()
{
	u16 color = 0;

	for (u32 i=0; i<2000; i++) {
		VICV->horizontal_border_color = color++;
	}

	VICV->horizontal_border_color = C64_BLACK;

	for (;;) {
		if (CIA->status_register)
			terminal_put_symbol(&main_terminal, CIA->key_next_ascii);
	}
}
