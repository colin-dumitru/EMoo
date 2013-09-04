#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "stdint.h"

#define REGISTER_ADDRESSING 0x05

/**
 * scale is also used what type of addressing is used by the instruction. REGISTER_ADDRESSING is used
 * for register addressing mode, otherwise using the SIB formula for memory addressing:
 * [disp + base + scale * index]
 */
class Instruction {
public:
    static const uint16_t GROUP_1_MASK = 0b11000000;
    static const uint16_t GROUP_2_MASK = 0b00111100;
    static const uint16_t GROUP_3_MASK = 0b00000010;
    static const uint16_t GROUP_4_MASK = 0b00000001;
    static const uint16_t OPERAND_MASK = 0b00011100;

    enum PrefixValue {
        LOCK             = 0b01000000,
        REPNE            = 0b10000000,
        REP              = 0b11000000,

        CS               = 0b00000100,
        SS               = 0b00001000,
        DS               = 0b00001100,
        ES               = 0b00010000,
        FS               = 0b00010100,
        GS               = 0b00011000,
        BRANCH_TAKEN     = 0b00100000,
        BRANCH_NOT_TAKEN = 0b01000000,

        OPERAND_SIZE     = 0b00000010,

        ADDRESS_SIZE     = 0b00000001
    };

    /**
      G1|  G2  |G3|G4

    Prefix group 1
    01: 0xF0: LOCK prefix
    10: 0xF2: REPNE/REPNZ prefix
    11: 0xF3: REP or REPE/REPZ prefix

    Prefix group 2
    0001: 0x2E: CS segment override
    0010: 0x36: SS segment override
    0011: 0x3E: DS segment override
    0100: 0x26: ES segment override
    0101: 0x64: FS segment override
    0110: 0x65: GS segment override
    0111: 0x2E: Branch not taken
    1000: 0x3E: Branch taken

    Prefix group 3
    1: 0x66: Operand-size override prefix

    Prefix group 4
    1: 0x67: Address-size override prefix
     */
    uint8_t prefix;
    uint8_t opcode;

    //memory addressing: value =[reg[base] + reg[index] + displacement]
    //register addressing: value = reg[base]
    uint8_t reg;

    //or immediate
    uint16_t displacement;
    uint8_t base;
    uint8_t index;

    bool registerAddressing;

    uint8_t length;
};


#endif // INSTRUCTION_H

