#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define ROM_MAJOR	0
#define ROM_MINOR	1
#define	ROM_BUILD_DATE	20210221

#define END_OF_HEAP	0x00180000	// this leaves 512k for supervisor stacksize
#define INITIAL_SSP	0x00200000	// initial value of superv stackp

#define VECTOR_000	0x00000000	// supervisor stackpointer
#define VECTOR_001	0x00000004	// reset vector (init progr counter)
#define VECTOR_002	0x00000008	// bus error
#define VECTOR_003	0x0000000c	// address error
#define VECTOR_004	0x00000010	// illegal instruction
#define VECTOR_005	0x00000014	// divide by zero
#define VECTOR_006	0x00000018
#define VECTOR_007	0x0000001c
#define VECTOR_008	0x00000020	// privilege violation
#define VECTOR_009	0x00000024	// trace
#define VECTOR_010	0x00000028	// line 1010 (line A)
#define VECTOR_011	0x0000002c	// line 1111 (line F)

#define VECTOR_024	0x00000060	// spurious interrupt
#define VECTOR_025	0x00000064	// interrupt level 1
#define VECTOR_026	0x00000068	// interrupt level 2 (vicv)
#define VECTOR_027	0x0000006c	// interrupt level 3
#define VECTOR_028	0x00000070	// interrupt level 4 (timers)
#define VECTOR_029	0x00000074	// interrupt level 5
#define VECTOR_030	0x00000078	// interrupt level 6
#define VECTOR_031	0x0000007c	// interrupt level 7 (non-maskable)
#define VECTOR_032	0x00000080	// Trap 0
#define VECTOR_033	0x00000084	// Trap 1
#define VECTOR_034	0x00000088	// Trap 2
#define VECTOR_035	0x0000008c	// Trap 3
#define VECTOR_036	0x00000090	// Trap 4
#define VECTOR_037	0x00000094	// Trap 5
#define VECTOR_038	0x00000098	// Trap 6
#define VECTOR_039	0x0000009c	// Trap 7
#define VECTOR_040	0x000000a0	// Trap 8
#define VECTOR_041	0x000000a4	// Trap 9
#define VECTOR_042	0x000000a8	// Trap 10
#define VECTOR_043	0x000000ac	// Trap 11
#define VECTOR_044	0x000000b0	// Trap 12
#define VECTOR_045	0x000000b4	// Trap 13
#define VECTOR_046	0x000000b8	// Trap 14
#define VECTOR_047	0x000000bc	// Trap 15

// VECTOR_048 - VECTOR_063 (0x000000c0 - 0x000000ff) unused / reserved?
// VECTOR_064 - VECTOR_255 (0x00000100 - 0x000003ff) user vectors

#define IO_BASE_ADDRESS		0x00fb0000

#define FD0_BASE_ADDRESS	IO_BASE_ADDRESS
#define FD0_STATUS_REGISTER	(FD0_BASE_ADDRESS+0x00)
#define FD0_CONTROL_REGISTER	(FD0_BASE_ADDRESS+0x01)
#define FD0_ERROR_STATUS	(FD0_BASE_ADDRESS+0x02)
#define FD0_IRQ_STATUS		_to_be_done_
#define FD0_SECTOR_NUMBER	(FD0_BASE_ADDRESS+0x04)
#define FD0_MEMORY_ADDRESS	(FD0_BASE_ADDRESS+0x08)

#define CIA_BASE_ADDRESS	(IO_BASE_ADDRESS+0x0300)
#define	CIA_STATUS_REGISTER	(CIA_BASE_ADDRESS+0x00)
#define CIA_CONTROL_REGISTER	(CIA_BASE_ADDRESS+0x01)
#define CIA_KEYBOARD_REP_DELAY	(CIA_BASE_ADDRESS+0x02)
#define	CIA_KEYBOARD_REP_SPEED	(CIA_BASE_ADDRESS+0x03)
#define	CIA_KEY_ASCII		(CIA_BASE_ADDRESS+0x04)
#define CIA_KEY_STATE_ARRAY	(CIA_BASE_ADDRESS+0x80)

#define VICV_BASE_ADDRESS	(IO_BASE_ADDRESS+0x0400)
#define VICV_ISR		(VICV_BASE_ADDRESS+0x00)
#define VICV_BUFFERSWAP		(VICV_BASE_ADDRESS+0x01)
#define VICV_HOR_BORDER_SIZE	(VICV_BASE_ADDRESS+0x02)
#define VICV_VER_BORDER_SIZE	(VICV_BASE_ADDRESS+0x03)
#define	VICV_HOR_BORDER_COLOR	(VICV_BASE_ADDRESS+0x04)
#define VICV_VER_BORDER_COLOR	(VICV_BASE_ADDRESS+0x06)

#define SIDS_BASE_ADDRESS  	(IO_BASE_ADDRESS+0x0500)
#define SID0_BASE_ADDRESS  	(SIDS_BASE_ADDRESS+0x00)
#define SID1_BASE_ADDRESS  	(SIDS_BASE_ADDRESS+0x20)
#define SIDS_EFFECTS		(SIDS_BASE_ADDRESS+0x80)

#define TIMER_BASE_ADDRESS	(IO_BASE_ADDRESS+0x600)
#define TIMER_STATUS_REGISTER	(TIMER_BASE_ADDRESS+0x00)
#define TIMER_CONTROL_REGISTER	(TIMER_BASE_ADDRESS+0x01)
#define TIMER_DATA_REGISTER	(TIMER_BASE_ADDRESS+0x02)

#define BLITTER_BASE_ADDRESS	(IO_BASE_ADDRESS+0x700)
#define BLITTER_CONTROL		(BLITTER_BASE_ADDRESS+0x00)
#define BLITTER_DATA		(BLITTER_BASE_ADDRESS+0x02)
#define BLITTER_CLEAR_COLOR	(BLITTER_BASE_ADDRESS+0x06)

// basic color palette
#define C64_BLACK       0xf000
#define C64_WHITE       0xffff
#define C64_RED	        0xf733
#define C64_CYAN        0xf8CC
#define C64_PURPLE      0xf849
#define C64_GREEN       0xf6a5
#define C64_BLUE        0xf339
#define C64_YELLOW      0xfee8
#define C64_ORANGE      0xf853
#define C64_BROWN       0xf531
#define C64_LIGHTRED	0xfb77
#define C64_DARKGREY	0xf444
#define C64_GREY	0xf777
#define C64_LIGHTGREEN	0xfbfa
#define C64_LIGHTBLUE	0xf67d
#define C64_LIGHTGREY	0xfaaa

#define CHAR_ROM        0xfb8000

// ascii definitions
#define	ASCII_NULL		0x00
#define	ASCII_BACKSPACE		0x08
#define	ASCII_LF		0x0a
#define	ASCII_CR		0x0d
#define	ASCII_CURSOR_DOWN	0x11
#define	ASCII_REVERSE_ON	0x12
#define	ASCII_CURSOR_RIGHT	0x1d
#define	ASCII_SPACE		0x20
#define	ASCII_CURSOR_UP		0x91
#define	ASCII_REVERSE_OFF	0x92
#define	ASCII_CURSOR_LEFT	0x9d

#endif
