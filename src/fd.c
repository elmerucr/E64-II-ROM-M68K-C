#include "fd.h"
#include "kernel.h"

int boo()
{
	FD0->sector_number = 0x13;
}
