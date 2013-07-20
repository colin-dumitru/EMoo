#include "machine.h"

Machine::Machine()
{
}

void Machine::reset() {
    cpu.ip = 0x0000;
    cpu.cs = 0xFFFF;
}
