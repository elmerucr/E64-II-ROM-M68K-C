#ifndef CIA_H
#define CIA_H

#include "kernel.h"

#define	CIA	((volatile struct cia_ic *) CIA_BASE_ADDRESS)

struct __attribute__((packed)) cia_ic {
	u8 status_register;
	u8 control_register;
	u8 keyboard_repeat_delay;
	u8 keyboard_repeat_speed;
	u8 key_next_ascii;
};

#endif
