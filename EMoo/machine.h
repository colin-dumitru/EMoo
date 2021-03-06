#ifndef MACHINE_H
#define MACHINE_H

#include "mem/ram.h"
#include "cpu/cpu.h"
#include "cpu/timing.h"
#include "io/porthandler.h"
#include "io/keyboard.h"
#include "io/ppi.h"
#include "io/vga.h"
#include <string.h>

class Machine
{
public:
    Cpu cpu;
    Ram ram;
    PortHandler portHandler;
    Timing timing;

    VGA vga;

    Machine();

    void reset();
    void step();
};


extern Machine machine;

#endif // MACHINE_H
