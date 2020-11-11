#ifndef TIMER_H
#define TIMER_H

#include "kernel.h"

#define	TIMER	((volatile struct timer_ic *) TIMER_BASE_ADDRESS)

struct __attribute__((packed)) timer_ic {
	u8  status_register;
	u8  control_register;
	u16 data_register;
};

enum timer_number {
	TIMER0,
	TIMER1,
	TIMER2,
	TIMER3
};

void timer_exception_handler();

extern void *timer0_vector;
extern void *timer1_vector;
extern void *timer2_vector;
extern void *timer3_vector;

void timer_turn_on(enum timer_number this_timer, u16 bpm);
void timer_turn_off(enum timer_number this_timer);
void timer_update_handler(enum timer_number this_timer, void *callback_function);

#endif
