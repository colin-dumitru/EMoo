#include "interpreter.h"
#include "cpu.h"

Interpreter::Interpreter()
{
    baseRegisterTable_ds[0] = &machine.cpu.ds;
    baseRegisterTable_ds[Instruction::DS] = &machine.cpu.ds;
    baseRegisterTable_ds[Instruction::CS] = &machine.cpu.cs;
    baseRegisterTable_ds[Instruction::ES] = &machine.cpu.es;
    baseRegisterTable_ds[Instruction::SS] = &machine.cpu.ss;
    baseRegisterTable_ds[Instruction::FS] = &machine.cpu.fs;
    baseRegisterTable_ds[Instruction::GS] = &machine.cpu.gs;

    baseRegisterTable_ss[0] = &machine.cpu.ss;
    baseRegisterTable_ss[Instruction::DS] = &machine.cpu.ds;
    baseRegisterTable_ss[Instruction::CS] = &machine.cpu.cs;
    baseRegisterTable_ss[Instruction::ES] = &machine.cpu.es;
    baseRegisterTable_ss[Instruction::SS] = &machine.cpu.ss;
    baseRegisterTable_ss[Instruction::FS] = &machine.cpu.fs;
    baseRegisterTable_ss[Instruction::GS] = &machine.cpu.gs;

    baseRegisterTableTable[Cpu::BX] = baseRegisterTable_ds;
    baseRegisterTableTable[Cpu::ZR] = baseRegisterTable_ds;
    baseRegisterTableTable[Cpu::BP] = baseRegisterTable_ss;

    /*
     * these are set so it desn't crash, but should never reach this case as
     * the base register value should only be BX, BP, ZR
     */
    baseRegisterTableTable[Cpu::AX] = baseRegisterTable_ds;
    baseRegisterTableTable[Cpu::CX] = baseRegisterTable_ds;
    baseRegisterTableTable[Cpu::DX] = baseRegisterTable_ds;
    baseRegisterTableTable[Cpu::SP] = baseRegisterTable_ds;
    baseRegisterTableTable[Cpu::SI] = baseRegisterTable_ds;
    baseRegisterTableTable[Cpu::DI] = baseRegisterTable_ds;
}

Interpreter::~Interpreter()
{
}

void Interpreter::reset() {
    memset(cache.cacheSet, false, RAM_SIZE);
}
