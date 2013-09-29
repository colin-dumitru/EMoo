#include "machine.h"
#include "cpu/interpreter.h"

Machine::Machine()
{
}

void Machine::reset() {    
    machine.portHandler.registerReader(0x60, Keyboard::read60);
    machine.portHandler.registerReader(0x61, PPI::read61);
    machine.portHandler.registerReader(0x62, PPI::read62);
    machine.portHandler.registerReader(0x63, PPI::read63);

    machine.portHandler.registerWriter(0x60, Keyboard::write60);
    machine.portHandler.registerWriter(0x61, PPI::write61);
    machine.portHandler.registerWriter(0x62, PPI::write62);
    machine.portHandler.registerWriter(0x63, PPI::write63);

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
