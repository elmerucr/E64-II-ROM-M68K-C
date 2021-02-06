#include "kernel.h"

#ifndef FD_H
#define FD_H

#define FD0			((volatile struct fd *) FD0_BASE_ADDRESS)
#define FD_CONTROL_READ		0b00000100
#define FD_CONTROL_WRITE	0b00001000
#define FD_CONTROL_RESET_ERROR	0b10000000

enum fd_error_list {
	FD_ERROR_NONE = 0,
	FD_ERROR_NO_DISK_INSIDE,
	FD_ERROR_MOTOR_IS_SPINNING,
	FD_ERROR_READING_PLANNED,
	FD_ERROR_READING,
	FD_ERROR_WRITING_PLANNED,
	FD_ERROR_WRITING,
	FD_ERROR_ILLEGAL_SECTOR,
	FD_ERROR_WRITE_PROTECT
};

struct __attribute__((packed)) fd {
	u8 status_register;
	u8 control_register;
	u8 error_status;
	u8 irq_status;

	u32 sector;
	u32 *buffer;
	u8 padding_byte_0;
	u8 padding_byte_1;
	u8 padding_byte_2;
	u8 padding_byte_3;
};

enum fd_error_list read_sector(u32 sector, void *buffer);
enum fd_error_list write_sector(u32 sector, void *buffer);

#endif
