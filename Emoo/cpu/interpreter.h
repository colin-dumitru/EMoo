#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "decoder.h"
#include "instruction.h"
#include "config.h"
#include "stdint.h"
#include "common.h"

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

    void interpret(Instruction* instruction);

public:
    Interpreter(Decoder* decoder);
    ~Interpreter();

    void interpret(uint32_t address);
};

inline void Interpreter::interpret(uint32_t address) {
    if(!cache.cacheSet[address]) {
        cache.cacheSet[address] = true;
        decoder->decode(address, &cache.instructionCache[address]);
    }
    interpret(&cache.instructionCache[address]);
}

inline void Interpreter::interpret(Instruction* instruction) {
}

#endif // INTERPRETER_H
