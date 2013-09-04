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

    void push(uint16_t value);
    uint16_t pop();

    void interpret(uint32_t address, Instruction* instruction);

    void interpretAddRmbRb(Instruction *instruction);
    void interpretAddRmwRw(Instruction *instruction);
    void interpretAddRbRmb(Instruction *instruction);
    void interpretAddRwRmw(Instruction *instruction);
    void interpretAddAlIb(Instruction *instruction);
    void interpretAddAxIw(Instruction *instruction);

    void interpretPushEs();
    void interpretPopEs();

    void interpretOrRmbRb(Instruction *instruction);
    void interpretOrRmwRw(Instruction *instruction);
    void interpretOrRbRmb(Instruction *instruction);
    void interpretOrRwRmw(Instruction *instruction);
    void interpretOrAlIb(Instruction *instruction);
    void interpretOrAxIw(Instruction *instruction);

    void interpretPushCs();
    void interpretPopCs();

    void interpretAdcRmbRb(Instruction *instruction);
    void interpretAdcRmwRw(Instruction *instruction);
    void interpretAdcRbRmb(Instruction *instruction);
    void interpretAdcRwRmw(Instruction *instruction);
    void interpretAdcAlIb(Instruction *instruction);
    void interpretAdcAxIw(Instruction *instruction);

    void interpretPushSs();
    void interpretPopSs();

    void interpretSbbRmbRb(Instruction *instruction);
    void interpretSbbRmwRw(Instruction *instruction);
    void interpretSbbRbRmb(Instruction *instruction);
    void interpretSbbRwRmw(Instruction *instruction);
    void interpretSbbAlIb(Instruction *instruction);
    void interpretSbbAxIw(Instruction *instruction);

    void interpretPushDs();
    void interpretPopDs();

    void interpretAndRmbRb(Instruction *instruction);
    void interpretAndRmwRw(Instruction *instruction);
    void interpretAndRbRmb(Instruction *instruction);
    void interpretAndRwRmw(Instruction *instruction);
    void interpretAndAlIb(Instruction *instruction);
    void interpretAndAxIw(Instruction *instruction);

    void interpretDaa();

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

inline void Interpreter::push(uint16_t value) {
    machine.cpu.sp.data -= 2;
    *((uint16_t*)(machine.ram.buffer + (machine.cpu.ss.data << 4) + machine.cpu.sp.data)) = value;
}

inline uint16_t Interpreter::pop() {
    static uint16_t tempValue;

    tempValue = *((uint16_t*)(machine.ram.buffer + (machine.cpu.ss.data << 4) + machine.cpu.sp.data));
    machine.cpu.sp.data += 2;
    return tempValue;
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
        /*0x00*/ &&opAddRmbRb, &&opAddRmwRw, &&opAddRbRmb, &&opAddRwRmw, &&opAddAlIb, &&opAddAxIw, &&opPushEs, &&opPopEs,
        /*0x08*/ &&opOrRmbRb, &&opOrRmwRw, &&opOrRbRmb, &&opOrRwRmw, &&opOrAlIb, &&opOrAxIw, &&opPushCs, &&opPopCs,
        /*0x10*/ &&opAdcRmbRb, &&opAdcRmwRw, &&opAdcRbRmb, &&opAdcRwRmw, &&opAdcAlIb, &&opAdcAxIw, &&opPushSs, &&opPopSs,
        /*0x18*/ &&opSbbRmbRb, &&opSbbRmwRw, &&opSbbRbRmb, &&opSbbRwRmw, &&opSbbAlIb, &&opSbbAxIw, &&opPushDs, &&opPopDs,
        /*0x20*/ &&opAndRmbRb, &&opAndRmwRw, &&opAndRbRmb, &&opAndRwRmw, &&opAndAlIb, &&opAndAxIw, &&error, &&opDaa
    };

    goto *jumpTable[instruction->opcode];

opAddRmbRb: return interpretAddRmbRb(instruction);
opAddRmwRw: return interpretAddRmwRw(instruction);
opAddRbRmb: return interpretAddRbRmb(instruction);
opAddRwRmw: return interpretAddRwRmw(instruction);
opAddAlIb: return interpretAddAlIb(instruction);
opAddAxIw: return interpretAddAxIw(instruction);

opPushEs: return interpretPushEs();
opPopEs: return interpretPopEs();

opOrRmbRb: return interpretOrRmbRb(instruction);
opOrRmwRw: return interpretOrRmwRw(instruction);
opOrRbRmb: return interpretOrRbRmb(instruction);
opOrRwRmw: return interpretOrRwRmw(instruction);
opOrAlIb: return interpretOrAlIb(instruction);
opOrAxIw: return interpretOrAxIw(instruction);

opPushCs: return interpretPushCs();
opPopCs: return interpretPopCs();

opAdcRmbRb: return interpretAdcRmbRb(instruction);
opAdcRmwRw: return interpretAdcRmwRw(instruction);
opAdcRbRmb: return interpretAdcRbRmb(instruction);
opAdcRwRmw: return interpretAdcRwRmw(instruction);
opAdcAlIb: return interpretAdcAlIb(instruction);
opAdcAxIw: return interpretAdcAxIw(instruction);

opPushSs: return interpretPushSs();
opPopSs: return interpretPopSs();

opSbbRmbRb: return interpretSbbRmbRb(instruction);
opSbbRmwRw: return interpretSbbRmwRw(instruction);
opSbbRbRmb: return interpretSbbRbRmb(instruction);
opSbbRwRmw: return interpretSbbRwRmw(instruction);
opSbbAlIb: return interpretSbbAlIb(instruction);
opSbbAxIw: return interpretSbbAxIw(instruction);

opPushDs: return interpretPushDs();
opPopDs: return interpretPopDs();

opAndRmbRb: return interpretAndRmbRb(instruction);
opAndRmwRw: return interpretAndRmwRw(instruction);
opAndRbRmb: return interpretAndRbRmb(instruction);
opAndRwRmw: return interpretAndRwRmw(instruction);
opAndAlIb: return interpretAndAlIb(instruction);
opAndAxIw: return interpretAndAxIw(instruction);

opDaa: return interpretDaa();

error:
    ERR("invalid opcode used");
    return;
}

inline void Interpreter::interpretAddRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 + operand2;
    *operand2Address = LOW(result);

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADD);
}

inline void Interpreter::interpretAddRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 + operand2;
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADD);
}

inline void Interpreter::interpretAddRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 + operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD);
}

inline void Interpreter::interpretAddRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 + operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD);
}

inline void Interpreter::interpretAddAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 + operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD);
}

inline void Interpreter::interpretAddAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 + operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD);
}

inline void Interpreter::interpretPushEs() {
    push(machine.cpu.es.data);
}

inline void Interpreter::interpretPopEs() {
    machine.cpu.es.data = pop();
}

inline void Interpreter::interpretOrRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 | operand2;
    *operand2Address = LOW(result);

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::LOG);
}

inline void Interpreter::interpretOrRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 | operand2;
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::LOG);
}

inline void Interpreter::interpretOrRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 | operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG);
}

inline void Interpreter::interpretOrRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 | operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG);
}

inline void Interpreter::interpretOrAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 | operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG);
}

inline void Interpreter::interpretOrAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 | operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG);
}

inline void Interpreter::interpretPushCs() {
    push(machine.cpu.cs.data);
}

inline void Interpreter::interpretPopCs() {
    machine.cpu.cs.data = pop();
}

inline void Interpreter::interpretAdcRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *operand2Address = LOW(result);

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretAdcRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretAdcRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretAdcRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretAdcAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretAdcAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretPushSs() {
    push(machine.cpu.ss.data);
}

inline void Interpreter::interpretPopSs() {
    machine.cpu.ss.data = pop();
}

inline void Interpreter::interpretSbbRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *operand2Address;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *operand2Address = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretSbbRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *((uint16_t*)operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretSbbRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretSbbRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretSbbAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretSbbAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretPushDs() {
    push(machine.cpu.ds.data);
}

inline void Interpreter::interpretPopDs() {
    machine.cpu.ds.data = pop();
}

inline void Interpreter::interpretAndRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *operand2Address;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 & operand2;
    *operand2Address = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretAndRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *((uint16_t*)operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 & operand2;
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretAndRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 & operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretAndRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 & operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretAndAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 & operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretAndAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 & operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC);
}

inline void Interpreter::interpretDaa() {

}


#endif // INTERPRETER_H
