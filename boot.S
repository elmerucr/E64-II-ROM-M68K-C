#include "kernel_constants.h"

    .text

    dc.l    0x00100000      | supervisor stackpointer (visible at 0x000000 in E64-II)
    dc.l    boot            | initial program counter (visible at 0x000004 in E64-II)

boot:
    movew   #0x2700,%sr     | disable all interrupts (useless on cold boot, matters for software reset)
    jmp     _init
