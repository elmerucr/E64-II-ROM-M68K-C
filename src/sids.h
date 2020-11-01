#include <stdint.h>

#ifndef SIDS_H
#define SIDS_H

struct __attribute__((packed)) sid
{
    uint16_t    voice_1_frequency;          // 0x00
    uint16_t    voice_1_pulsewidth;         // 0x02
    uint8_t     voice_1_control_register;   // 0x04
    uint8_t     voice_1_attack_decay;       // 0x05
    uint8_t     voice_1_sustain_release;    // 0x06

    uint8_t     padding_byte_1;


    uint16_t    voice_2_frequency;          // 0x08
    uint16_t    voice_2_pulsewidth;         // 0x0a
    uint8_t     voice_2_control_register;   // 0x0c
    uint8_t     voice_2_attack_decay;       // 0x0d
    uint8_t     voice_2_sustain_release;    // 0x0e

    uint8_t     padding_byte_2;


    uint16_t    voice_3_frequency;          // 0x10
    uint16_t    voice_3_pulsewidth;         // 0x12
    uint8_t     voice_3_control_register;   // 0x14
    uint8_t     voice_3_attack_decay;       // 0x15
    uint8_t     voice_3_sustain_release;    // 0x16

    uint8_t     padding_byte_3;


    uint16_t    filter_cutoff;              // 0x18
    uint8_t     filter_resonance;           // 0x1a
    uint8_t     filter_mode_volume;         // 0x1b


    uint8_t     pot_x;                      // 0x1c
    uint8_t     pot_y;                      // 0x1d
    uint8_t     osc3_random;                // 0x1e
    uint8_t     env3;                       // 0x1f
};

struct __attribute__((packed)) sid_balance_registers
{
    uint8_t sid0_left;
    uint8_t sid0_right;
    uint8_t sid1_left;
    uint8_t sid1_right;

    uint8_t padding_byte_0;
    uint8_t padding_byte_1;
    uint8_t padding_byte_2;
    uint8_t padding_byte_3;
};

enum notes
{
    N_C0_, N_C0S, N_D0_, N_D0S, N_E0_, N_F0_, N_F0S, N_G0_, N_G0S, N_A0_, N_A0S, N_B0_,
    N_C1_, N_C1S, N_D1_, N_D1S, N_E1_, N_F1_, N_F1S, N_G1_, N_G1S, N_A1_, N_A1S, N_B1_,
    N_C2_, N_C2S, N_D2_, N_D2S, N_E2_, N_F2_, N_F2S, N_G2_, N_G2S, N_A2_, N_A2S, N_B2_,
    N_C3_, N_C3S, N_D3_, N_D3S, N_E3_, N_F3_, N_F3S, N_G3_, N_G3S, N_A3_, N_A3S, N_B3_,
    N_C4_, N_C4S, N_D4_, N_D4S, N_E4_, N_F4_, N_F4S, N_G4_, N_G4S, N_A4_, N_A4S, N_B4_,
    N_C5_, N_C5S, N_D5_, N_D5S, N_E5_, N_F5_, N_F5S, N_G5_, N_G5S, N_A5_, N_A5S, N_B5_,
    N_C6_, N_C6S, N_D6_, N_D6S, N_E6_, N_F6_, N_F6S, N_G6_, N_G6S, N_A6_, N_A6S, N_B6_,
    N_C7_, N_C7S, N_D7_, N_D7S, N_E7_, N_F7_, N_F7S, N_G7_, N_G7S, N_A7_, N_A7S,
};

extern const uint16_t note_frequencies[];

void sids_reset();
void sids_welcome_sound();

#endif
