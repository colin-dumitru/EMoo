#ifndef CPU_H
#define CPU_H

#include "mem/register16.h"
#include "config.h"
#include "common.h"

MACHINE_AWARE

class InstructionCache;
class Interpreter;
class Decoder;
class Instruction;

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

    Interpreter* interpreter;
    Decoder* decoder;
};

class Decoder {
private:
    Cpu* cpu;


public:
    Decoder(Cpu* cpu);

    void decode(uint32_t address, Instruction* instruction);
};

class Interpreter {
private:
    Cpu* cpu;
    InstructionCache* cache;
public:
    Interpreter(Cpu* cpu);
    ~Interpreter();

    void interpret(uint32_t address);
};

class Instruction {
public:
    void (Interpreter::*handler)(Instruction*);
    uint32_t op1;
    uint32_t op2;
};

class InstructionCache {

private:
    Cpu* cpu;

    Instruction instructionCache[RAM_SIZE];
    void (InstructionCache::*cacheHandlers[RAM_SIZE])(uint32_t) = {&InstructionCache::executeNew};

    void executeFromCache(uint32_t address);
    void executeNew(uint32_t address);

public:
    InstructionCache(Cpu* cpu);

};

#endif // CPU_H
