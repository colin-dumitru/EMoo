#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "decoder.h"
#include "instruction.h"
#include "config.h"
#include "stdint.h"
#include "common.h"

class Cpu;

class InstructionCache {

private:

public:
    Instruction instructionCache[RAM_SIZE];
    bool cacheSet[RAM_SIZE] = {false};
};

class Interpreter {
private:
    InstructionCache cache;
    Decoder* decoder;

    void interpret(uint32_t& address, Instruction* instruction);

    void interpretAddRmbRb(uint32_t& address, Instruction *instruction);
    void interpretAddRmwRw(uint32_t& address, Instruction *instruction);
    void interpretAddRbRmb(uint32_t& address, Instruction *instruction);
    void interpretAddRwRmw(uint32_t& address, Instruction *instruction);
    void interpretAddAlIb(uint32_t& address, Instruction *instruction);
    void interpretAddAxIw(uint32_t& address, Instruction *instruction);

public:
    Interpreter(Cpu* decoder);
    ~Interpreter();

    uint8_t interpret(uint32_t address);
};

inline uint8_t Interpreter::interpret(uint32_t address) {
    if(!cache.cacheSet[address]) {
        cache.cacheSet[address] = true;
        decoder->decode(address, &cache.instructionCache[address]);
    }
    interpret(address, &cache.instructionCache[address]);

    return cache.instructionCache[address].length;
}

inline void Interpreter::interpret(uint32_t& address, Instruction* instruction) {
    static const void * jumpTable[] = {
        /*0x00*/ &&opAddRmbRb, &&opAddRmwRw, &&opAddRbRmb, &&opAddRwRmw, &&opAddAlIb, &&opAddAxIw
    };

    goto *jumpTable[address++];

opAddRmbRb:
    return interpretAddRmbRb(address, instruction);
opAddRmwRw:
    return interpretAddRmwRw(address, instruction);
opAddRbRmb:
    return interpretAddRbRmb(address, instruction);
opAddRwRmw:
    return interpretAddRwRmw(address, instruction);
opAddAlIb:
    return interpretAddAlIb(address, instruction);
opAddAxIw:
    return interpretAddAxIw(address, instruction);
end:
    return;
}

inline void Interpreter::interpretAddRmbRb(uint32_t& address, Instruction *instruction) {
    if(instruction->registerAddressing) {

    } else {

    }
    //flags
}

inline void Interpreter::interpretAddRmwRw(uint32_t& address, Instruction *instruction) {

}

inline void Interpreter::interpretAddRbRmb(uint32_t& address, Instruction *instruction) {

}

inline void Interpreter::interpretAddRwRmw(uint32_t& address, Instruction *instruction) {

}

inline void Interpreter::interpretAddAlIb(uint32_t& address, Instruction *instruction) {

}

inline void Interpreter::interpretAddAxIw(uint32_t& address, Instruction *instruction) {

}

#endif // INTERPRETER_H
