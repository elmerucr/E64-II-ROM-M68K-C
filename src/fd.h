#include "kernel.h"

#ifndef FD_H
#define FD_H

#define FD0	((volatile struct fd *) FD0_BASE_ADDRESS)

enum fd_error_list {
	FD_ERROR_NONE = 0,
	FD_ERROR_PREVIOUS
};

struct __attribute__((packed)) fd {
	u8 status_register;
	u8 control_register;
	u8 error_status;
	u8 irq_status;

	u32 sector_number;
	u32 *memory_address;
	u8 padding_byte_0;
	u8 padding_byte_1;
	u8 padding_byte_2;
	u8 padding_byte_3;
};

enum fd_error_list read_sector(u32 sector_number, void *memory_address);

#endif
