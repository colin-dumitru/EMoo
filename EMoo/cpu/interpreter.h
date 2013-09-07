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
#include "interrupthandler.h"

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

    void interpretSubRmbRb(Instruction *instruction);
    void interpretSubRmwRw(Instruction *instruction);
    void interpretSubRbRmb(Instruction *instruction);
    void interpretSubRwRmw(Instruction *instruction);
    void interpretSubAlIb(Instruction *instruction);
    void interpretSubAxIw(Instruction *instruction);

    void interpretDas();

    void interpretXorRmbRb(Instruction *instruction);
    void interpretXorRmwRw(Instruction *instruction);
    void interpretXorRbRmb(Instruction *instruction);
    void interpretXorRwRmw(Instruction *instruction);
    void interpretXorAlIb(Instruction *instruction);
    void interpretXorAxIw(Instruction *instruction);

    void interpretAaa();

    void interpretCmpRmbRb(Instruction *instruction);
    void interpretCmpRmwRw(Instruction *instruction);
    void interpretCmpRbRmb(Instruction *instruction);
    void interpretCmpRwRmw(Instruction *instruction);
    void interpretCmpAlIb(Instruction *instruction);
    void interpretCmpAxIw(Instruction *instruction);

    void interpretAas();

    void interpretIncEax();
    void interpretIncEcx();
    void interpretIncEdx();
    void interpretIncEbx();
    void interpretIncEsp();
    void interpretIncEbp();
    void interpretIncEsi();
    void interpretIncEdi();

    void interpretDecEax();
    void interpretDecEcx();
    void interpretDecEdx();
    void interpretDecEbx();
    void interpretDecEsp();
    void interpretDecEbp();
    void interpretDecEsi();
    void interpretDecEdi();

    void interpretPushEax();
    void interpretPushEcx();
    void interpretPushEdx();
    void interpretPushEbx();
    void interpretPushEsp();
    void interpretPushEbp();
    void interpretPushEsi();
    void interpretPushEdi();

    void interpretPopEax();
    void interpretPopEcx();
    void interpretPopEdx();
    void interpretPopEbx();
    void interpretPopEsp();
    void interpretPopEbp();
    void interpretPopEsi();
    void interpretPopEdi();

    void interpretPusha();
    void interpretPopa();
    void interpretBound(Instruction* instruction);

    void interpretPushIw(Instruction* instruction);
    void interpretImulIw(Instruction* instruction);
    void interpretPushIb(Instruction* instruction);
    void interpretImulIb(Instruction* instruction);

    void interpretInsb();
    void interpretInsw();
    void interpretOutsb();
    void interpretOutsw();

    void interpretJo(Instruction* instruction);
    void interpretJno(Instruction* instruction);
    void interpretJb(Instruction* instruction);
    void interpretJnb(Instruction* instruction);
    void interpretJz(Instruction* instruction);
    void interpretJnz(Instruction* instruction);
    void interpretJbe(Instruction* instruction);
    void interpretJa(Instruction* instruction);
    void interpretJs(Instruction* instruction);
    void interpretJns(Instruction* instruction);
    void interpretJpe(Instruction* instruction);
    void interpretJpo(Instruction* instruction);
    void interpretJl(Instruction* instruction);
    void interpretJge(Instruction* instruction);
    void interpretJle(Instruction* instruction);
    void interpretJg(Instruction* instruction);


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
        /*0x20*/ &&opAndRmbRb, &&opAndRmwRw, &&opAndRbRmb, &&opAndRwRmw, &&opAndAlIb, &&opAndAxIw, &&error, &&opDaa,
        /*0x28*/ &&opSubRmbRb, &&opSubRmwRw, &&opSubRbRmb, &&opSubRwRmw, &&opSubAlIb, &&opSubAxIw, &&error, &&opDas,
        /*0x30*/ &&opXorRmbRb, &&opXorRmwRw, &&opXorRbRmb, &&opXorRwRmw, &&opXorAlIb, &&opXorAxIw, &&error, &&opAaa, /*dendi*/
        /*0x38*/ &&opCmpRmbRb, &&opCmpRmwRw, &&opCmpRbRmb, &&opCmpRwRmw, &&opCmpAlIb, &&opCmpAxIw, &&error, &&opAas,
        /*0x40*/ &&opIncEax, &&opIncEcx, &&opIncEdx, &&opIncEbx, &&opIncEsp, &&opIncEbp, &&opIncEsi, &&opIncEdi,
        /*0x48*/ &&opDecEax, &&opDecEcx, &&opDecEdx, &&opDecEbx, &&opDecEsp, &&opDecEbp, &&opDecEsi, &&opDecEdi,
        /*0x50*/ &&opPushEax, &&opPushEcx, &&opPushEdx, &&opPushEbx, &&opPushEsp, &&opPushEbp, &&opPushEsi, &&opPushEdi,
        /*0x58*/ &&opPopEax, &&opPopEcx, &&opPopEdx, &&opPopEbx, &&opPopEsp, &&opPopEbp, &&opPopEsi, &&opPopEdi,
        /*0x60*/ &&opPusha, &&opPopa, &&opBound, &&error, &&error, &&error, &&error, &&error,
        /*0x68*/ &&opPushIw, &&opImulIw, &&opPushIb, &&opImulIb, &&opInsb, &&opInsw, &&opOutsb, &&opOutsw,
        /*0x70*/ &&opJo, &&opJno, &&opJb, &&opJnb, &&opJz, &&opJnz, &&opJbe, &&opJa,
        /*0x78*/ &&opJs, &&opJns, &&opJpe, &&opJpo, &&opJl, &&opJge, &&opJle, &&opJg,
        /*0x80*/
        /*0x88*/
        /*0x90*/
        /*0x98*/
        /*0xA0*/
        /*0xA8*/
        /*0xB0*/
        /*0xB8*/
        /*0xC0*/
        /*0xC8*/
        /*0xD0*/
        /*0xD8*/
        /*0xE0*/
        /*0xE8*/
        /*0xF0*/
        /*0xF8*/
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

opSubRmbRb: return interpretSubRmbRb(instruction);
opSubRmwRw: return interpretSubRmwRw(instruction);
opSubRbRmb: return interpretSubRbRmb(instruction);
opSubRwRmw: return interpretSubRwRmw(instruction);
opSubAlIb: return interpretSubAlIb(instruction);
opSubAxIw: return interpretSubAxIw(instruction);

opDas: return interpretDas();

opXorRmbRb: return interpretXorRmbRb(instruction);
opXorRmwRw: return interpretXorRmwRw(instruction);
opXorRbRmb: return interpretXorRbRmb(instruction);
opXorRwRmw: return interpretXorRwRmw(instruction);
opXorAlIb: return interpretXorAlIb(instruction);
opXorAxIw: return interpretXorAxIw(instruction);

opAaa: return interpretAaa();

opCmpRmbRb: return interpretCmpRmbRb(instruction);
opCmpRmwRw: return interpretCmpRmwRw(instruction);
opCmpRbRmb: return interpretCmpRbRmb(instruction);
opCmpRwRmw: return interpretCmpRwRmw(instruction);
opCmpAlIb: return interpretCmpAlIb(instruction);
opCmpAxIw: return interpretCmpAxIw(instruction);

opAas: return interpretAas();

opIncEax: return interpretIncEax();
opIncEcx: return interpretIncEcx();
opIncEdx: return interpretIncEdx();
opIncEbx: return interpretIncEbx();
opIncEsp: return interpretIncEsp();
opIncEbp: return interpretIncEbp();
opIncEsi: return interpretIncEsi();
opIncEdi: return interpretIncEdi();

opDecEax: return interpretDecEax();
opDecEcx: return interpretDecEcx();
opDecEdx: return interpretDecEdx();
opDecEbx: return interpretDecEbx();
opDecEsp: return interpretDecEsp();
opDecEbp: return interpretDecEbp();
opDecEsi: return interpretDecEsi();
opDecEdi: return interpretDecEdi();

opPushEax: return interpretPushEax();
opPushEcx: return interpretPushEcx();
opPushEdx: return interpretPushEdx();
opPushEbx: return interpretPushEbx();
opPushEsp: return interpretPushEsp();
opPushEbp: return interpretPushEbp();
opPushEsi: return interpretPushEsi();
opPushEdi: return interpretPushEdi();

opPopEax: return interpretPopEax();
opPopEcx: return interpretPopEcx();
opPopEdx: return interpretPopEdx();
opPopEbx: return interpretPopEbx();
opPopEsp: return interpretPopEsp();
opPopEbp: return interpretPopEbp();
opPopEsi: return interpretPopEsi();
opPopEdi: return interpretPopEdi();

opPusha: return interpretPusha();
opPopa: return interpretPopa();
opBound: return interpretBound(instruction);

opImulIw: return interpretImulIw(instruction);
opPushIw: return interpretPushIw(instruction);
opImulIb: return interpretImulIb(instruction);
opPushIb: return interpretPushIb(instruction);
opInsb: return interpretInsb();
opInsw: return interpretInsw();
opOutsb: return interpretOutsb();
opOutsw: return interpretOutsw();

opJo: interpretJo(instruction);
opJno: interpretJno(instruction);
opJb: interpretJb(instruction);
opJnb: interpretJnb(instruction);
opJz: interpretJz(instruction);
opJnz: interpretJnz(instruction);
opJbe: interpretJbe(instruction);
opJa: interpretJa(instruction);
opJs: interpretJs(instruction);
opJns: interpretJns(instruction);
opJpe: interpretJpe(instruction);
opJpo: interpretJpo(instruction);
opJl: interpretJl(instruction);
opJge: interpretJge(instruction);
opJle: interpretJle(instruction);
opJg: interpretJg(instruction);

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

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADD8);
}

inline void Interpreter::interpretAddRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 + operand2;
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADD16);
}

inline void Interpreter::interpretAddRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 + operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
}

inline void Interpreter::interpretAddRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 + operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD16);
}

inline void Interpreter::interpretAddAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 + operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
}

inline void Interpreter::interpretAddAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 + operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD16);
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

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretOrRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 | operand2;
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretOrRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 | operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretOrRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 | operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretOrAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 | operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretOrAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 | operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
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

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADC8);
}

inline void Interpreter::interpretAdcRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADC16);
}

inline void Interpreter::interpretAdcRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
}

inline void Interpreter::interpretAdcRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC16);
}

inline void Interpreter::interpretAdcAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
}

inline void Interpreter::interpretAdcAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC16);
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

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
}

inline void Interpreter::interpretSbbRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *((uint16_t*)operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB16);
}

inline void Interpreter::interpretSbbRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
}

inline void Interpreter::interpretSbbRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB16);
}

inline void Interpreter::interpretSbbAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
}

inline void Interpreter::interpretSbbAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB16);
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

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretAndRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *((uint16_t*)operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 & operand2;
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretAndRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 & operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretAndRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 & operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretAndAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 & operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretAndAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 & operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretDaa() {
    static uint8_t tmpAf;
    static uint8_t tmpCf;

    if(((LOW(machine.cpu.ax.data) & 0x0F) > 9) || machine.cpu.flagsRegister.getAf()) {
        LOW(machine.cpu.ax.data) += 6;
        tmpAf = 1;
    } else {
        tmpAf = 0;
    }

    if((LOW(machine.cpu.ax.data) > 0x9F) || machine.cpu.flagsRegister.getCf()){
        LOW(machine.cpu.ax.data) += 0x60;
        tmpCf = 1;
    } else {
        tmpCf = 0;
    }

    machine.cpu.flagsRegister.set(tmpCf, tmpAf, LOW(machine.cpu.ax.data), FlagsRegister::DAA8);
}

inline void Interpreter::interpretSubRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *operand2Address;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 - operand2;
    *operand2Address = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

inline void Interpreter::interpretSubRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *((uint16_t*)operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 - operand2;
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

inline void Interpreter::interpretSubRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 - operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

inline void Interpreter::interpretSubRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 - operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

inline void Interpreter::interpretSubAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 - operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

inline void Interpreter::interpretSubAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 - operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

inline void Interpreter::interpretDas() {
    static uint8_t tmpAf;
    static uint8_t tmpCf;

    if(((LOW(machine.cpu.ax.data) & 0x0F) > 9) || machine.cpu.flagsRegister.getAf()) {
        LOW(machine.cpu.ax.data) -= 6;
        tmpAf = 1;
    } else {
        tmpAf = 0;
    }

    if((LOW(machine.cpu.ax.data) > 0x9F) || machine.cpu.flagsRegister.getCf()) {
        LOW(machine.cpu.ax.data) -= 0x60;
        tmpCf = 1;
    } else {
        tmpCf = 0;
    }

    machine.cpu.flagsRegister.set(tmpCf, tmpAf, LOW(machine.cpu.ax.data), FlagsRegister::DAA8);
}

inline void Interpreter::interpretXorRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *operand2Address;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 ^ operand2;
    *operand2Address = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretXorRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *((uint16_t*)operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 ^ operand2;
    *((uint16_t*)operand2Address) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretXorRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 ^ operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretXorRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 ^ operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretXorAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 ^ operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretXorAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 ^ operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretAaa() {
    static uint8_t tmpAf;
    static uint8_t tmpCf;

    if (((LOW(machine.cpu.ax.data) & 0x0F) > 9) || machine.cpu.flagsRegister.getAf()) {
        LOW(machine.cpu.ax.data) += 6;
        HIGH(machine.cpu.ax.data) += 1;

        tmpAf = 1;
        tmpCf = 1;
    } else {
        tmpAf = 0;
        tmpCf = 0;
    }

    LOW(machine.cpu.ax.data) &= 0x0F;

    machine.cpu.flagsRegister.set(tmpCf, tmpAf, LOW(machine.cpu.ax.data), FlagsRegister::DAA8);
}

inline void Interpreter::interpretCmpRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *operand2Address;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

inline void Interpreter::interpretCmpRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *((uint16_t*)operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

inline void Interpreter::interpretCmpRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *operand2Address;

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

inline void Interpreter::interpretCmpRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *((uint16_t*)operand2Address);

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

inline void Interpreter::interpretCmpAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->displacement;

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

inline void Interpreter::interpretCmpAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->displacement;

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

inline void Interpreter::interpretAas() {
    static uint8_t tmpAf;
    static uint8_t tmpCf;

    if (((LOW(machine.cpu.ax.data) & 0x0F) > 9) || machine.cpu.flagsRegister.getAf()) {
        LOW(machine.cpu.ax.data) -= 6;
        HIGH(machine.cpu.ax.data) -= 1;

        tmpAf = 1;
        tmpCf = 1;
    } else {
        tmpAf = 0;
        tmpCf = 0;
    }

    LOW(machine.cpu.ax.data) &= 0x0F;

    machine.cpu.flagsRegister.set(tmpCf, tmpAf, LOW(machine.cpu.ax.data), FlagsRegister::DAA8);
}

inline void Interpreter::interpretIncEax() {
    operand1 = machine.cpu.ax.data;
    result = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::INC16);
}

inline void Interpreter::interpretIncEcx() {
    operand1 = machine.cpu.cx.data;
    result = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::INC16);
}

inline void Interpreter::interpretIncEdx() {
    operand1 = machine.cpu.dx.data;
    result = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::INC16);
}

inline void Interpreter::interpretIncEbx() {
    operand1 = machine.cpu.bx.data;
    result = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::INC16);
}

inline void Interpreter::interpretIncEsp() {
    operand1 = machine.cpu.sp.data;
    result = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::INC16);
}

inline void Interpreter::interpretIncEbp() {
    operand1 = machine.cpu.bp.data;
    result = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::INC16);
}

inline void Interpreter::interpretIncEsi() {
    operand1 = machine.cpu.si.data;
    result = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::INC16);
}

inline void Interpreter::interpretIncEdi() {
    operand1 = machine.cpu.di.data;
    result = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::INC16);
}

inline void Interpreter::interpretDecEax() {
    operand1 = machine.cpu.ax.data;
    result = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::DEC16);
}

inline void Interpreter::interpretDecEcx() {
    operand1 = machine.cpu.cx.data;
    result = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::DEC16);
}

inline void Interpreter::interpretDecEdx() {
    operand1 = machine.cpu.dx.data;
    result = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::DEC16);
}

inline void Interpreter::interpretDecEbx() {
    operand1 = machine.cpu.bx.data;
    result = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::DEC16);
}

inline void Interpreter::interpretDecEsp() {
    operand1 = machine.cpu.sp.data;
    result = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::DEC16);
}

inline void Interpreter::interpretDecEbp() {
    operand1 = machine.cpu.bp.data;
    result = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::DEC16);
}

inline void Interpreter::interpretDecEsi() {
    operand1 = machine.cpu.si.data;
    result = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::DEC16);
}

inline void Interpreter::interpretDecEdi() {
    operand1 = machine.cpu.di.data;
    result = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), result, FlagsRegister::DEC16);
}

inline void Interpreter::interpretPushEax() {
    push(machine.cpu.ax.data);
}

inline void Interpreter::interpretPushEcx() {
    push(machine.cpu.cx.data);
}

inline void Interpreter::interpretPushEdx() {
    push(machine.cpu.dx.data);
}

inline void Interpreter::interpretPushEbx() {
    push(machine.cpu.bx.data);
}

inline void Interpreter::interpretPushEsp() {
    push(machine.cpu.sp.data);
}

inline void Interpreter::interpretPushEbp() {
    push(machine.cpu.bp.data);
}

inline void Interpreter::interpretPushEsi() {
    push(machine.cpu.si.data);
}

inline void Interpreter::interpretPushEdi() {
    push(machine.cpu.di.data);
}

inline void Interpreter::interpretPopEax() {
    machine.cpu.ax.data = pop();
}

inline void Interpreter::interpretPopEcx() {
    machine.cpu.cx.data = pop();
}

inline void Interpreter::interpretPopEdx() {
    machine.cpu.dx.data = pop();
}

inline void Interpreter::interpretPopEbx() {
    machine.cpu.bx.data = pop();
}

inline void Interpreter::interpretPopEsp() {
    machine.cpu.sp.data = pop();
}

inline void Interpreter::interpretPopEbp() {
    machine.cpu.bp.data = pop();
}

inline void Interpreter::interpretPopEsi() {
    machine.cpu.si.data = pop();
}

inline void Interpreter::interpretPopEdi() {
    machine.cpu.di.data = pop();
}

inline void Interpreter::interpretPusha() {
    static uint16_t tempSp;

    tempSp = machine.cpu.sp.data;

    push(machine.cpu.ax.data);
    push(machine.cpu.cx.data);
    push(machine.cpu.dx.data);
    push(machine.cpu.bx.data);
    push(tempSp);
    push(machine.cpu.bp.data);
    push(machine.cpu.si.data);
    push(machine.cpu.di.data);
}

inline void Interpreter::interpretPopa() {
    machine.cpu.di.data = pop();
    machine.cpu.si.data = pop();
    machine.cpu.bp.data = pop();
    machine.cpu.sp.data += 2;
    machine.cpu.bx.data = pop();
    machine.cpu.dx.data = pop();
    machine.cpu.cx.data = pop();
    machine.cpu.ax.data = pop();
}

inline void Interpreter::interpretBound(Instruction *instruction) {
    static uint16_t index, lowerBound, upperBound;

    decodeAddress16(instruction);

    index = machine.cpu.registerTable[instruction->reg]->data;
    lowerBound = *((uint16_t*)operand2Address);
    upperBound = *(((uint16_t*)operand2Address) + 1);

    if(index < lowerBound || index > (upperBound + 2)) {
        machine.cpu.interruptHandler->call(5);
    }
}

inline void Interpreter::interpretImulIw(Instruction *instruction) {
    uint32_t tempResult;

    decodeAddress16(instruction);

    operand1 = *((uint16_t*)operand2Address);
    operand2 = instruction->displacement;

    tempResult = operand1 * operand2;

    machine.cpu.registerTable[instruction->reg]->data = tempResult;

    machine.cpu.flagsRegister.set(tempResult >= 0xFFFF0000, FlagsRegister::IMUL16);
}

inline void Interpreter::interpretPushIw(Instruction *instruction) {
    push(instruction->displacement);
}

inline void Interpreter::interpretImulIb(Instruction *instruction) {
    uint32_t tempResult;

    decodeAddress8(instruction);

    operand1 = *((uint16_t*)operand2Address);
    operand2 = instruction->displacement;

    tempResult = operand1 * operand2;

    machine.cpu.registerTable[instruction->reg]->data = tempResult;

    machine.cpu.flagsRegister.set(tempResult >= 0xFFFF0000, FlagsRegister::IMUL8);
}

inline void Interpreter::interpretPushIb(Instruction *instruction) {
    push(instruction->displacement);
}

inline void Interpreter::interpretInsb() {
    LOW(machine.cpu.ax.data) = machine.portHandler.in8(machine.cpu.dx.data);
}

inline void Interpreter::interpretInsw() {
    machine.cpu.ax.data = machine.portHandler.in16(machine.cpu.dx.data);
}

inline void Interpreter::interpretOutsb() {
    machine.portHandler.out8(machine.cpu.dx.data, LOW(machine.cpu.ax.data));
}

inline void Interpreter::interpretOutsw() {
    machine.portHandler.out16(machine.cpu.dx.data, machine.cpu.ax.data);
}

inline void Interpreter::interpretJo(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJno(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJb(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getCf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}
inline void Interpreter::interpretJnb(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getCf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJz(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJnz(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJbe(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getCf() || machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJa(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getCf() && !machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJs(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getSf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJns(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getSf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJpe(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getPf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJpo(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getPf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJl(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getSf() != machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJge(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getSf() == machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJle(Instruction *instruction) {
    if((machine.cpu.flagsRegister.getSf() != machine.cpu.flagsRegister.getOf()) || machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

inline void Interpreter::interpretJg(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getZf() && (machine.cpu.flagsRegister.getOf() == machine.cpu.flagsRegister.getSf())) {
        machine.cpu.ip.data += (int8_t)instruction->displacement;
    }
}

#endif // INTERPRETER_H
