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
class InterruptHandler;

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

    enum REGISTER_ADRESS {
        AL = 0b000,
        CL = 0b001,
        DL = 0b010,
        BL = 0b011,
        AH = 0b100,
        CH = 0b101,
        DH = 0b110,
        BH = 0b111
    };

    enum SEGMENT_REGISTER {
        ES = 0b000,
        CS = 0b001,
        SS = 0b010,
        DS = 0b011
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
    uint8_t* registerAddressTable[8];
    Register16* segmentRegisterTable[4];

    FlagsRegister flagsRegister;

    Interpreter* interpreter;
    Decoder* decoder;
    InterruptHandler* interruptHandler;
};

#endif // CPU_H
