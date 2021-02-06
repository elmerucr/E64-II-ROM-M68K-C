#include "fd.h"
#include "kernel.h"

enum fd_error_list read_sector(u32 sector_number, void *buffer_address) {
	if (FD0->status_register & 0x80) {
		return FD0->error_status;
	} else {
		FD0->sector = sector_number;
		FD0->buffer = buffer_address;
		FD0->control_register = FD_CONTROL_READ;
	}
	while ((FD0->status_register & 0b00000100)) {
		// wait loop
		// NEEDS WORK
	}
	return FD0->error_status;
}

enum fd_error_list write_sector(u32 sector_number, void *buffer_address) {
	if (FD0->status_register & 0x80) {
		return FD0->error_status;
	} else {
		FD0->sector = sector_number;
		FD0->buffer = buffer_address;
		FD0->control_register = FD_CONTROL_WRITE;
	}
	while ((FD0->status_register & 0b00001000)) {
		// wait loop
		// NEEDS WORK
	}
	return FD0->error_status;
}
