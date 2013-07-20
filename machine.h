#ifndef MACHINE_H
#define MACHINE_H

#include "cpu/cpu.h"
#include "mem/ram.h"

class Machine
{
public:
    Cpu cpu;
    Ram ram;

    Machine();

    void reset();
};

#endif // MACHINE_H
