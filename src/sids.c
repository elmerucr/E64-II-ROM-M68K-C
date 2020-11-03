#include "sids.h"
#include "definitions.h"
#include "kernel.h"

struct sid *sid0 = (struct sid *)SID0_BASE_ADDRESS;
struct sid *sid1 = (struct sid *)SID1_BASE_ADDRESS;

struct sid_balance_registers *balance_registers = (struct sid_balance_registers *)(SIDS_BASE_ADDRESS+0x80);
//struct sid_balance_registers *balance_registers = (struct sid_balance_registers *)0x00200080;

void sids_reset()
{
    for(uint8_t i=0; i<64; i++)
    {
        uint32_t address = SIDS_BASE_ADDRESS+i;
        pokeb(address, 0x00);
    }

    sid0->filtermode_volume = 0xf;
    sid1->filtermode_volume = 0xf;

    for(uint8_t i=0; i<8; i++)
    {
        uint32_t address = SIDS_BASE_ADDRESS+0x80+i;
        pokeb(address, 0xff);
    }
}

void sids_welcome_sound()
{
    sid0->voice_1_frequency = note_frequencies[N_D3_];
    sid0->voice_1_attack_decay = 0b00001001;
    sid0->voice_1_pulsewidth = 0xf0f;
    balance_registers->sid0_left = 0xff;
    balance_registers->sid0_right = 0x10;
    sid0->voice_1_control_register = 0b01000001;

    sid1->voice_1_frequency = note_frequencies[N_A3_];
    sid1->voice_1_attack_decay = 0b00001001;
    sid1->voice_1_pulsewidth = 0xf0f;
    balance_registers->sid1_left = 0x10;
    balance_registers->sid1_right = 0xff;
    sid1->voice_1_control_register = 0b01000001;
}

const uint16_t note_frequencies[95] =
{
    0x0116, 0x0127, 0x0139, 0x014B, 0x015F, 0x0174, 0x018A, 0x01A1, 0x01BA, 0x01D4, 0x01F0, 0x020E,	    // N_C0_ to N_B0_
    0x022D, 0x024E, 0x0271, 0x0296, 0x02BE, 0x02E7, 0x0314, 0x0342, 0x0374, 0x03A9, 0x03E0, 0x041B,	    // N_C1_ to N_B1_
    0x045A, 0x049C, 0x04E2, 0x052D, 0x057B, 0x05CF, 0x0627, 0x0685, 0x06E8, 0x0751, 0x07C1, 0x0837,	    // N_C2_ to N_B2_
    0x08B4, 0x0938, 0x09C4, 0x0A59, 0x0AF7, 0x0B9D, 0x0C4E, 0x0D0A, 0x0DD0, 0x0EA2, 0x0F81, 0x106D,	    // N_C3_ to N_B3_
    0x1167, 0x1270, 0x1389, 0x14B2, 0x15ED, 0x173B, 0x189C, 0x1A13, 0x1BA0, 0x1D45, 0x1F02, 0x20DA,	    // N_C4_ to N_B4_
    0x22CE, 0x24E0, 0x2711, 0x2964, 0x2BDA, 0x2E76, 0x3139, 0x3426, 0x3740, 0x3A89, 0x3E04, 0x41B4,	    // N_C5_ to N_B5_
    0x459C, 0x49C0, 0x4E23, 0x52C8, 0x57B4, 0x5CEB, 0x6272, 0x684C, 0x6E80, 0x7512, 0x7C08, 0x8368,	    // N_C6_ to N_B6_
    0x8B39, 0x9380, 0x9C45, 0xA590, 0xAF68, 0xB9D6, 0xC4E3, 0xD099, 0xDD00, 0xEA24, 0xF810	            // N_C7_ to N_A7S
};
