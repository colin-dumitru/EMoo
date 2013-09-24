#include "machine.h"
#include "cpu/interpreter.h"

Machine::Machine()
{
}

void Machine::reset() {    
    cpu.ip.data = 0x0000;
    cpu.cs.data = 0x0000;
    cpu.interpreter->reset();
}

void Machine:: step() {
    cpu.interpreter->interpret(uint32_t((cpu.cs.data << 4) + cpu.ip.data));
}

Machine machine;
