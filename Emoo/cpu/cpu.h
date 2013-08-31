#ifndef CPU_H
#define CPU_H

#include "mem/register16.h"
#include "config.h"
#include "common.h"
#include "decoder.h"
#include "instruction.h"

MACHINE_AWARE

class InstructionCache;
class Interpreter;

class Cpu {
public:
    enum REGISTER {
        AX = 0b000,
        CX = 0b001,
        DX = 0b010,
        BX = 0b011,
        SP = 0b100,
        BP = 0b101,
        SI = 0b110,
        DI = 0b111,
        //zero
        ZR = 0b1000
    };

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

    //special register which is always 0
    Register16 zero;

    Register16* registerTable[9];

    FlagsRegister flagsRegister;

    Interpreter* interpreter;
    Decoder* decoder;
};

#endif // CPU_H
