#include "kernel_constants.h"

        .text

        /* Supervisor stackpointer and initial program counter are
         * stored at the start of rom image. The logic in E64-II
         * makes the first 8 bytes of this rom image visible on
         * addresses 0 to 7 (vector 0 and 1).
         */
        dc.l    0x00100000
        dc.l    boot

boot:
        movew   #0x2700,%sr             // disable all interrupts (useless on cold boot, matters for software reset)
        move.l  #0xc00000,VECTOR_045    // put address in Trap 13 vector
        //trap    #13
        jmp     _kinit
