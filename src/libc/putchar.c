#include <stdio.h>
#include "tty.h"

int putchar(int character)
{
	tty_putchar((u8)character);
	return character;
}
