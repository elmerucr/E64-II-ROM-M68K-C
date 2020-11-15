#include "timer.h"

void timer_turn_on(enum timer_number this_timer, u16 bpm)
{
	TIMER->data_register = bpm;
	TIMER->control_register |= (0b1 << this_timer);
}

void timer_turn_off(enum timer_number this_timer)
{
	TIMER->control_register &= (0b11111111 - (0b1 << this_timer));
}

void timer_update_handler(enum timer_number this_timer, void *callback_function)
{
	switch (this_timer) {
	case TIMER0:
		timer0_vector = callback_function;
		break;
	case TIMER1:
		timer1_vector = callback_function;
		break;
	case TIMER2:
		timer2_vector = callback_function;
		break;
	case TIMER3:
		timer3_vector = callback_function;
		break;
	case TIMER4:
		timer4_vector = callback_function;
		break;
	case TIMER5:
		timer5_vector = callback_function;
		break;
	case TIMER6:
		timer6_vector = callback_function;
		break;
	case TIMER7:
		timer7_vector = callback_function;
		break;
	default:
		break;
	}
}
