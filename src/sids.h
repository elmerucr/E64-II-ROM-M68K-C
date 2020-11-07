#include "kernel.h"

#ifndef SIDS_H
#define SIDS_H

struct __attribute__((packed)) sid {
	u16    voice_1_frequency;          // 0x00
	u16    voice_1_pulsewidth;         // 0x02
	u8     voice_1_control_register;   // 0x04
	u8     voice_1_attack_decay;       // 0x05
	u8     voice_1_sustain_release;    // 0x06

	u8     padding_byte_1;

	u16    voice_2_frequency;          // 0x08
	u16    voice_2_pulsewidth;         // 0x0a
	u8     voice_2_control_register;   // 0x0c
	u8     voice_2_attack_decay;       // 0x0d
	u8     voice_2_sustain_release;    // 0x0e

	u8     padding_byte_2;

	u16    voice_3_frequency;          // 0x10
	u16    voice_3_pulsewidth;         // 0x12
	u8     voice_3_control_register;   // 0x14
	u8     voice_3_attack_decay;       // 0x15
	u8     voice_3_sustain_release;    // 0x16

	u8     padding_byte_3;

	u16    filter_cutoff;              // 0x18
	u8     filter_resonance;           // 0x1a
	u8     filtermode_volume;          // 0x1b

	u8     pot_x;                      // 0x1c
	u8     pot_y;                      // 0x1d
	u8     osc3_random;                // 0x1e
	u8     env3;                       // 0x1f
};

struct __attribute__((packed)) sid_balance_registers {
	u8 sid0_left;
	u8 sid0_right;
	u8 sid1_left;
	u8 sid1_right;

	u8 padding_byte_0;
	u8 padding_byte_1;
	u8 padding_byte_2;
	u8 padding_byte_3;
};

enum notes {
	N_C0_, N_C0S, N_D0_, N_D0S, N_E0_, N_F0_, N_F0S, N_G0_, N_G0S, N_A0_, N_A0S, N_B0_,
	N_C1_, N_C1S, N_D1_, N_D1S, N_E1_, N_F1_, N_F1S, N_G1_, N_G1S, N_A1_, N_A1S, N_B1_,
	N_C2_, N_C2S, N_D2_, N_D2S, N_E2_, N_F2_, N_F2S, N_G2_, N_G2S, N_A2_, N_A2S, N_B2_,
	N_C3_, N_C3S, N_D3_, N_D3S, N_E3_, N_F3_, N_F3S, N_G3_, N_G3S, N_A3_, N_A3S, N_B3_,
	N_C4_, N_C4S, N_D4_, N_D4S, N_E4_, N_F4_, N_F4S, N_G4_, N_G4S, N_A4_, N_A4S, N_B4_,
	N_C5_, N_C5S, N_D5_, N_D5S, N_E5_, N_F5_, N_F5S, N_G5_, N_G5S, N_A5_, N_A5S, N_B5_,
	N_C6_, N_C6S, N_D6_, N_D6S, N_E6_, N_F6_, N_F6S, N_G6_, N_G6S, N_A6_, N_A6S, N_B6_,
	N_C7_, N_C7S, N_D7_, N_D7S, N_E7_, N_F7_, N_F7S, N_G7_, N_G7S, N_A7_, N_A7S,
};

extern const u16 note_frequencies[];

void sids_reset();
void sids_welcome_sound();

#endif
