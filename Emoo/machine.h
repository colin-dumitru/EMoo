#ifndef MACHINE_H
#define MACHINE_H

#include "mem/ram.h"
#include "cpu/cpu.h"

class Machine
{
public:
    Cpu cpu;
    Ram ram;

    Machine();

    void reset();
} machine;

#endif // MACHINE_H
