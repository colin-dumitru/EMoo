#include "interrupthandler.h"
#include "machine.h"
#include "interpreter.h"

InterruptHandler::InterruptHandler()
{
}

void InterruptHandler::call(uint16_t interrupt) {
    machine.cpu.interpreter->push(machine.cpu.flagsRegister.toWord());
    machine.cpu.interpreter->push(machine.cpu.cs.data);
    machine.cpu.interpreter->push(machine.cpu.ip.data);

    machine.cpu.cs.data = *WORD(&machine.ram.buffer[(interrupt << 2) + 2]);
    machine.cpu.ip.data = *WORD(&machine.ram.buffer[(interrupt << 2)]);
    machine.cpu.flagsRegister.itf = 0;
    machine.cpu.flagsRegister.tf = 0;
}
