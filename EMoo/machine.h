#ifndef MACHINE_H
#define MACHINE_H

#include "mem/ram.h"
#include "cpu/cpu.h"
#include "io/porthandler.h"
#include "io/keyboard.h"
#include <string.h>

class Machine
{
public:
    Cpu cpu;
    Ram ram;
    PortHandler portHandler;

    Machine();

    void reset();
    void step();
};

extern Machine machine;

#endif // MACHINE_H
