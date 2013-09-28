#include "machine.h"
#include "cpu/interpreter.h"

Machine::Machine()
{
}

void Machine::reset() {    
    cpu.ip.data = 0x0000;
    cpu.cs.data = 0x0000;
    cpu.interpreter->reset();

    /*
     * I'm not sure why and who sets this flag normally, as it appears that the BIOS expects this
     * to be 41 - equipment flag for VGA. If anyone knows why, please contact as I've spent an entire afternoon
     * trying to figure out.*/
    //ram.buffer[0x410] = 0x41;
}

void Machine:: step() {
    cpu.interpreter->interpret(uint32_t((cpu.cs.data << 4) + cpu.ip.data));
}

Machine machine;
