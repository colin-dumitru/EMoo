#include "decoder.h"

Decoder::Decoder(Ram* ram) : ram(ram)
{
}

bool* Decoder::buildPrefixTable() {
    bool table[0xFF] = {false};

    table[0xF0] = true;
    table[0xF2] = true;
    table[0xF3] = true;

    table[0x2E] = true;
    table[0x36] = true;
    table[0x3E] = true;
    table[0x26] = true;
    table[0x64] = true;
    table[0x65] = true;
    table[0x2E] = true;
    table[0x3E] = true;

    table[0x66] = true;

    table[0x67] = true;

    return table;
}

uint8_t* Decoder::buildPrefixEquivalenceTable() {
    uint8_t table[13];

    table[0xF0] = Instruction::LOCK;
    table[0xF2] = Instruction::REPNE;
    table[0xF3] = Instruction::REP;

    table[0x2E] = Instruction::CS;
    table[0x36] = Instruction::SS;
    table[0x3E] = Instruction::DS;
    table[0x26] = Instruction::ES;
    table[0x64] = Instruction::FS;
    table[0x65] = Instruction::GS;
    table[0x2E] = Instruction::BRANCH_NOT_TAKEN;
    table[0x3E] = Instruction::BRANCH_TAKEN;

    table[0x66] = Instruction::OPERAND_SIZE;

    table[0x67] = Instruction::ADDRESS_SIZE;

    return table;
}
