#include "machine.h"

Machine::Machine()
{
}

void Machine::reset() {
    cpu.ip.data = 0x0000;
    cpu.cs.data = 0xFFFF;
}

void Machine::step() {
    cpu.interpreter->interpret(cpu.cs.data << 4 + cpu.ip.data);
}


Machine machine;
