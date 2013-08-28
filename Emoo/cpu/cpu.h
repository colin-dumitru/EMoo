#ifndef CPU_H
#define CPU_H

#include "mem/register16.h"
#include "config.h"
#include "common.h"
#include "interpreter.h"
#include "decoder.h"
#include "instruction.h"

MACHINE_AWARE

class InstructionCache;

class Cpu {
public:
    Cpu();
    ~Cpu();

    Register16 ax;
    Register16 bx;
    Register16 cx;
    Register16 dx;
    Register16 si;
    Register16 di;
    Register16 sp;
    Register16 bp;
    Register16 ip;
    Register16 cs;
    Register16 ds;
    Register16 ss;
    Register16 es;
    Register16 fs;
    Register16 gs;

    Register16 registerTable[];

    FlagsRegister flagsRegister;

    Interpreter* interpreter;
    Decoder* decoder;
};

#endif // CPU_H
