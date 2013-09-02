#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "decoder.h"
#include "instruction.h"
#include "config.h"
#include "stdint.h"
#include "common.h"
#include "cpu.h"
#include "mem/ram.h"
#include "machine.h"

class InstructionCache {

private:

public:
    Instruction instructionCache[RAM_SIZE];
    bool cacheSet[RAM_SIZE] = {false};
};

class Interpreter {
private:
    Register16* baseRegisterTable[Instruction::GS + 1];

    InstructionCache cache;

    uint16_t operand1;
    uint16_t operand2;
    uint16_t result;
    uint8_t* operand2Address;

    void decodeAddress8(Instruction* instruction);
    void decodeAddress16(Instruction* instruction);
    void decodeMemoryAddress(Instruction* instruction);

    uint16_t decodeBaseRegisterValue(Instruction* instruction);
    uint16_t decodeRelativeAddress(Instruction* instruction);

    void interpret(uint32_t address, Instruction* instruction);

    void interpretAddRmbRb(uint32_t& address, Instruction *instruction);
    void interpretAddRmwRw(uint32_t& address, Instruction *instruction);
    void interpretAddRbRmb(uint32_t& address, Instruction *instruction);
    void interpretAddRwRmw(uint32_t& address, Instruction *instruction);
    void interpretAddAlIb(uint32_t& address, Instruction *instruction);
    void interpretAddAxIw(uint32_t& address, Instruction *instruction);

public:
    Interpreter();
    ~Interpreter();

    void reset();

    uint8_t interpret(uint32_t address);
};

inline void Interpreter::decodeAddress8(Instruction *instruction) {
    if(instruction->registerAddressing) {
        operand2Address = machine.cpu.registerAddressTable[instruction->base];
    } else {
        decodeMemoryAddress(instruction);
    }
}

inline void Interpreter::decodeAddress16(Instruction *instruction) {
    if(instruction->registerAddressing) {
        operand2Address = (uint8_t*)&machine.cpu.registerTable[instruction->base]->data;
    } else {
        decodeMemoryAddress(instruction);
    }
}

inline void Interpreter::decodeMemoryAddress(Instruction *instruction) {
    static uint16_t baseRegisterValue;
    static uint16_t relativeAddress;

    //these functions and variables are so horbly named, that I will surely forget what they are in two weeks
    baseRegisterValue = decodeBaseRegisterValue(instruction);
    relativeAddress = decodeRelativeAddress(instruction);

    operand2Address = &machine.ram.buffer[(baseRegisterValue << 4) + relativeAddress];
}

inline uint16_t Interpreter::decodeBaseRegisterValue(Instruction *instruction) {
    return baseRegisterTable[instruction->prefix & Instruction::OPERAND_MASK]->data;
}

inline uint16_t Interpreter::decodeRelativeAddress(Instruction *instruction) {
    return machine.cpu.registerTable[instruction->base]->data
            + machine.cpu.registerTable[instruction->index]->data
            + instruction->displacement;
}

inline uint8_t Interpreter::interpret(uint32_t address) {
    if(!cache.cacheSet[address]) {
        cache.cacheSet[address] = true;
        machine.cpu.decoder->decode(address, &cache.instructionCache[address]);
    }
    interpret(address, &cache.instructionCache[address]);

    return cache.instructionCache[address].length;
}

inline void Interpreter::interpret(uint32_t address, Instruction* instruction) {
    static const void * jumpTable[] = {
        /*0x00*/ &&opAddRmbRb, &&opAddRmwRw, &&opAddRbRmb, &&opAddRwRmw, &&opAddAlIb, &&opAddAxIw
    };

    goto *jumpTable[instruction->opcode];

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
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 + operand2;
    *operand2Address = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD);
}

inline void Interpreter::interpretAddRmwRw(uint32_t& address, Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 + operand2;
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD);
}

inline void Interpreter::interpretAddRbRmb(uint32_t& address, Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 + operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD);
}

inline void Interpreter::interpretAddRwRmw(uint32_t& address, Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 + operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD);
}

inline void Interpreter::interpretAddAlIb(uint32_t& address, Instruction *instruction) {

}

inline void Interpreter::interpretAddAxIw(uint32_t& address, Instruction *instruction) {

}

#endif // INTERPRETER_H
