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

    uint16_t    voice_2_frequency;          // 0x07 $#@^$%#@^%$ word access to uneven memory address?
    uint16_t    voice_2_pulsewidth;
    uint8_t     voice_2_control_register;
    uint8_t     voice_2_attack_decay;
    uint8_t     voice_2_sustain_release;

    uint16_t    voice_3_frequency;
    uint16_t    voice_3_pulsewidth;
    uint8_t     voice_3_control_register;
    uint8_t     voice_3_attack_decay;
    uint8_t     voice_3_sustain_release;

    uint16_t    filter_cutoff;
    uint8_t     filter_resonance;
    uint8_t     filter_mode_volume;

    uint8_t     pot_x;
    uint8_t     pot_y;
    uint8_t     osc3_random;
    uint8_t     env3;
};

void sids_reset();

#endif
