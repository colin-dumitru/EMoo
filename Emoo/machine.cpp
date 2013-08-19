#include "machine.h"

Machine::Machine()
{
}

void Machine::reset() {
    cpu.ip.data = 0x0000;
    cpu.cs.data = 0xFFFF;
}


Machine machine;
