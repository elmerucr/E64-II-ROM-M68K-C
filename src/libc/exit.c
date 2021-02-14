#include "stdlib.h"
#include "kernel.h"

void exit(int status)
{
	panic();
}
