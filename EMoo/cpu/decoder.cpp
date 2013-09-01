#include "decoder.h"
#include "cpu.h"

Decoder::Decoder(Ram* ram) : ram(ram)
{
    baseRegisterTable[0] = Cpu::BX;
    baseRegisterTable[1] = Cpu::BX;
    baseRegisterTable[2] = Cpu::BP;
    baseRegisterTable[3] = Cpu::BP;
    baseRegisterTable[4] = Cpu::ZR;
    baseRegisterTable[5] = Cpu::ZR;
    baseRegisterTable[6] = Cpu::BP;
    baseRegisterTable[7] = Cpu::BX;

    indexRegisterTable[0] = Cpu::SI;
    indexRegisterTable[1] = Cpu::DI;
    indexRegisterTable[2] = Cpu::SI;
    indexRegisterTable[3] = Cpu::DI;
    indexRegisterTable[4] = Cpu::SI;
    indexRegisterTable[5] = Cpu::DI;
    indexRegisterTable[6] = Cpu::ZR;
    indexRegisterTable[7] = Cpu::ZR;

    prefixTable[0xF0] = true;
    prefixTable[0xF2] = true;
    prefixTable[0xF3] = true;
    prefixTable[0x2E] = true;
    prefixTable[0x36] = true;
    prefixTable[0x3E] = true;
    prefixTable[0x26] = true;
    prefixTable[0x64] = true;
    prefixTable[0x65] = true;
    prefixTable[0x2E] = true;
    prefixTable[0x3E] = true;
    prefixTable[0x66] = true;
    prefixTable[0x67] = true;

    prefixEqTable[0xF0] = Instruction::LOCK;
    prefixEqTable[0xF2] = Instruction::REPNE;
    prefixEqTable[0xF3] = Instruction::REP;
    prefixEqTable[0x2E] = Instruction::CS;
    prefixEqTable[0x36] = Instruction::SS;
    prefixEqTable[0x3E] = Instruction::DS;
    prefixEqTable[0x26] = Instruction::ES;
    prefixEqTable[0x64] = Instruction::FS;
    prefixEqTable[0x65] = Instruction::GS;
    prefixEqTable[0x2E] = Instruction::BRANCH_NOT_TAKEN;
    prefixEqTable[0x3E] = Instruction::BRANCH_TAKEN;
    prefixEqTable[0x66] = Instruction::OPERAND_SIZE;
    prefixEqTable[0x67] = Instruction::ADDRESS_SIZE;
}
