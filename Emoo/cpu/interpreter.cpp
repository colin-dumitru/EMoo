#include "interpreter.h"
#include "cpu.h"

Interpreter::Interpreter()
{
    baseRegisterTable[0] = &machine.cpu.ds;
    baseRegisterTable[Instruction::DS] = &machine.cpu.ds;
    baseRegisterTable[Instruction::CS] = &machine.cpu.cs;
    baseRegisterTable[Instruction::ES] = &machine.cpu.es;
    baseRegisterTable[Instruction::SS] = &machine.cpu.ss;
    baseRegisterTable[Instruction::FS] = &machine.cpu.fs;
    baseRegisterTable[Instruction::GS] = &machine.cpu.gs;
}

Interpreter::~Interpreter()
{
}
