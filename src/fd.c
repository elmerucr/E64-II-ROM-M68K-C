#include "fd.h"
#include "kernel.h"

enum fd_error_list read_sector(u32 sector_number, void *memory_address) {
	if (FD0->status_register & 0x80) {
		return FD_ERROR_PREVIOUS;
	} else {
		FD0->sector_number = sector_number;
		FD0->memory_address = memory_address;
		FD0->control_register = 0b00000100;

	}
	while ((FD0->status_register & 0b00000100)) {
		//tty_puts("boe");
	}
	return FD_ERROR_NONE;
}
