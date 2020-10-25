#ifndef KERNEL_CONSTANTS_H
#define KERNEL_CONSTANTS_H

#define VECTOR_000          0x00000000      // supervisor stackpointer
#define VECTOR_001          0x00000004      // reset vector (initial program counter)
#define VECTOR_002          0x00000008      // bus error
#define VECTOR_003          0x0000000c      // address error
#define VECTOR_004          0x00000010      // illegal instruction
#define VECTOR_005          0x00000014      // divide by zero
#define VECTOR_006          0x00000018
#define VECTOR_007          0x0000001c
#define VECTOR_008          0x00000020      // privilege violation
#define VECTOR_009          0x00000024      // trace
#define VECTOR_010          0x00000028      // line 1010 (line A)
#define VECTOR_011          0x0000002c      // line 1111 (line F)

#define VECTOR_024          0x00000060      // spurious interrupt
#define VECTOR_025          0x00000064      // interrupt level 1
#define VECTOR_026          0x00000068      // interrupt level 2
#define VECTOR_027          0x0000006c      // interrupt level 3
#define VECTOR_028          0x00000070      // interrupt level 4
#define VECTOR_029          0x00000074      // interrupt level 5
#define VECTOR_030          0x00000078      // interrupt level 6
#define VECTOR_031          0x0000007c      // interrupt level 7 (non-maskable interrupt)
#define VECTOR_032          0x00000080      // Trap 0
#define VECTOR_033          0x00000084      // Trap 1
#define VECTOR_034          0x00000088      // Trap 2
#define VECTOR_035          0x0000008c      // Trap 3
#define VECTOR_036          0x00000090      // Trap 4
#define VECTOR_037          0x00000094      // Trap 5
#define VECTOR_038          0x00000098      // Trap 6
#define VECTOR_039          0x0000009c      // Trap 7
#define VECTOR_040          0x000000a0      // Trap 8
#define VECTOR_041          0x000000a4      // Trap 9
#define VECTOR_042          0x000000a8      // Trap 10
#define VECTOR_043          0x000000ac      // Trap 11
#define VECTOR_044          0x000000b0      // Trap 12
#define VECTOR_045          0x000000b4      // Trap 13
#define VECTOR_046          0x000000b8      // Trap 14
#define VECTOR_047          0x000000bc      // Trap 15

// VECTOR_048 - VECTOR_063 (0x000000c0 - 0x000000ff) unused / reserved?
// VECTOR_064 - VECTOR_255 (0x00000100 - 0x000003ff) user vectors

#define IO_BASE_ADDRESS     0x00fb0000

#define VICV_BASE_ADDRESS   (IO_BASE_ADDRESS+0x0400)
#define	VICV_BORDER_COLOR	(VICV_BASE_ADDRESS+0x00)
#define VICV_BORDER_SIZE	(VICV_BASE_ADDRESS+0x0c)

#define SID_BASE_ADDRESS    (IO_BASE_ADDRESS+0x0500)

#endif
