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

    uint32_t operand1;
    uint32_t operand2;
    uint32_t result;
    uint8_t* operand2Address;

    void decodeAddress8(Instruction* instruction);
    void decodeAddress16(Instruction* instruction);
    void decodeMemoryAddress(Instruction* instruction);

    uint16_t decodeBaseRegisterValue(Instruction* instruction);
    uint16_t decodeRelativeAddress(Instruction* instruction);

    void push(uint16_t value);
    uint16_t pop();

    bool isLoopFinished(Instruction *instruction);
    void processLoop(Instruction *instruction, uint8_t operandSize);
    void interpretBitGrp8(Instruction *instruction);
    void interpretBitGrp16(Instruction *instruction);

    void interpret(Instruction* instruction);

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

    void interpretInsb(Instruction *instruction);
    void interpretInsw(Instruction *instruction);
    void interpretOutsb(Instruction *instruction);
    void interpretOutsw(Instruction *instruction);

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

    void interpretGrpRmbIb(Instruction* instruction);
    void interpretGrpRmwIw(Instruction* instruction);
    void interpretGrpRmwIb(Instruction* instruction);
    void interpretTestRmbRb(Instruction* instruction);
    void interpretTestRmwRw(Instruction* instruction);
    void interpretXchgRmbRb(Instruction* instruction);
    void interpretXchgRmwRw(Instruction* instruction);

    void interpretMovRmbRb(Instruction* instruction);
    void interpretMovRmwRw(Instruction* instruction);
    void interpretMovRbRmb(Instruction* instruction);
    void interpretMovRwRmw(Instruction* instruction);
    void interpretMovRmwSr(Instruction* instruction);
    void interpretLea(Instruction* instruction);
    void interpretMovSrRmw(Instruction* instruction);
    void interpretPopRmw(Instruction* instruction);

    void interpretXchgEcxEax();
    void interpretXchgEdxEax();
    void interpretXchgEbxEax();
    void interpretXchgEspEax();
    void interpretXchgEbpEax();
    void interpretXchgEsiEax();
    void interpretXchgEdiEax();

    void interpretCbw();
    void interpretCwd();
    void interpretCall(Instruction* instruction);
    void interpretWait();
    void interpretPushF();
    void interpretPopF();
    void interpretSahF();
    void interpretLahF();

    void interpretMovAlRmb(Instruction* instruction);
    void interpretMovAxRmw(Instruction* instruction);
    void interpretMovRmbAl(Instruction* instruction);
    void interpretMovRmwAx(Instruction* instruction);
    void interpretMovsb(Instruction* instruction);
    void interpretMovsw(Instruction* instruction);
    void interpretCmpsb(Instruction* instruction);
    void interpretCmpsw(Instruction* instruction);

    void interpretTestAlIb(Instruction* instruction);
    void interpretTestAxIw(Instruction* instruction);
    void interpretStosb(Instruction* instruction);
    void interpretStosw(Instruction* instruction);
    void interpretLodsb(Instruction* instruction);
    void interpretLodsw(Instruction* instruction);
    void interpretScasb(Instruction* instruction);
    void interpretScasw(Instruction* instruction);

    void interpretMovAlIb(Instruction* instruction);
    void interpretMovClIb(Instruction* instruction);
    void interpretMovDlIb(Instruction* instruction);
    void interpretMovBlIb(Instruction* instruction);
    void interpretMovAhIb(Instruction* instruction);
    void interpretMovChIb(Instruction* instruction);
    void interpretMovDhIb(Instruction* instruction);
    void interpretMovBhIb(Instruction* instruction);
    void interpretMovEaxIw(Instruction* instruction);
    void interpretMovEcxIw(Instruction* instruction);
    void interpretMovEdxIw(Instruction* instruction);
    void interpretMovEbxIw(Instruction* instruction);
    void interpretMovEspIw(Instruction* instruction);
    void interpretMovEbpIw(Instruction* instruction);
    void interpretMovEsiIw(Instruction* instruction);
    void interpretMovEdiIw(Instruction* instruction);

    void interpretGrpRmbIb2(Instruction* instruction);
    void interpretGrpRmwIb2(Instruction* instruction);
    void interpretRetIw(Instruction* instruction);
    void interpretRet(Instruction *instruction);
    void interpretLes(Instruction* instruction);
    void interpretLds(Instruction* instruction);
    void interpretMovRmbIb(Instruction* instruction);
    void interpretMovRmwIw(Instruction* instruction);

    void interpretEnter(Instruction* instruction);
    void interpretLeave();
    void interpretRetfIw(Instruction* instruction);
    void interpretRetf(Instruction* instruction);
    void interpretInt3();
    void interpretIntIb(Instruction* instruction);
    void interpretInto();
    void interpretIret(Instruction* instruction);

    void interpretGrpRmb1(Instruction* instruction);
    void interpretGrpRmw1(Instruction* instruction);
    void interpretGrpRmbCl(Instruction* instruction);
    void interpretGrpRmwCl(Instruction* instruction);
    void interpretAam(Instruction* instruction);
    void interpretAad(Instruction* instruction);
    void interpretXlat();
    void interpretXlat2(Instruction* instruction);

    void interpretLoopnz(Instruction* instruction);
    void interpretLoopz(Instruction* instruction);
    void interpretLoop(Instruction* instruction);
    void interpretJcxz(Instruction* instruction);
    void interpretInAlIb(Instruction* instruction);
    void interpretInEaxIb(Instruction* instruction);
    void interpretOutIbAl(Instruction* instruction);
    void interpretOutIbEax(Instruction* instruction);

    void interpretCallIw(Instruction* instruction);
    void interpretJmp(Instruction* instruction);
    void interpretJmpFar(Instruction* instruction);
    void interpretJmpShort(Instruction* instruction);
    void interpretInAlEdx();
    void interpretInEaxEdx();
    void interpretOutEdxAl();
    void interpretOutEdxEax();

    void interpretLock();
    void interpretHlt();
    void interpretCmc();
    void interpretGrpIb3(Instruction* instruction);
    void interpretGrpIw3(Instruction* instruction);

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
    *WORD((machine.ram.buffer + (machine.cpu.ss.data << 4) + machine.cpu.sp.data)) = value;
}

inline uint16_t Interpreter::pop() {
    static uint16_t tempValue;

    tempValue = *WORD((machine.ram.buffer + (machine.cpu.ss.data << 4) + machine.cpu.sp.data));
    machine.cpu.sp.data += 2;
    return tempValue;
}

inline uint8_t Interpreter::interpret(uint32_t address) {
    if(!cache.cacheSet[address]) {
        cache.cacheSet[address] = true;
        machine.cpu.decoder->decode(address, &cache.instructionCache[address]);
    }
    interpret(&cache.instructionCache[address]);

    return cache.instructionCache[address].length;
}

inline bool Interpreter::isLoopFinished(Instruction* instruction) {
    switch (instruction->prefix & Instruction::GROUP_1_MASK) {
    case Instruction::REP:
        return machine.cpu.cx.data == 0 || !machine.cpu.flagsRegister.getZf();
    case Instruction::REPNE:
        return machine.cpu.cx.data == 0 || machine.cpu.flagsRegister.getZf();
    }
    return true;
}

inline void Interpreter::processLoop(Instruction *instruction, uint8_t operandSize) {
    if(machine.cpu.flagsRegister.df) {
        machine.cpu.si.data -= operandSize;
        machine.cpu.di.data -= operandSize;
    } else {
        machine.cpu.si.data += operandSize;
        machine.cpu.di.data += operandSize;
    }

    /*-1 if the loop has not finished, 0 otherwise*/
    if(!isLoopFinished(instruction)) {
        machine.cpu.cx.data -= 1;
        machine.cpu.ip.data -= instruction->length;
    }
}

inline void Interpreter::interpretBitGrp8(Instruction* instruction) {
    static const void* jumpTable[] = {
        &&opRol, &&opRor, &&opRcl, &&opRcr, &&opShl, &&opShr, &&opShl, &&opSar
    };

    goto *jumpTable[instruction->reg];

opRol:
    operand2 = operand2 % 8;
    result = (operand1 << operand2) | (operand1 >> (8 - operand2));
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), (*operand2Address << 8) | *operand2Address, machine.cpu.flagsRegister.result,
                                         FlagsRegister::ROL | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRor:
    operand2 = operand2 % 8;
    result = (operand1 >> operand2) | (operand1 << (8 - operand2));
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), (*operand2Address << 8) | *operand2Address, machine.cpu.flagsRegister.result,
                                         FlagsRegister::ROR | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRcl:
    operand2 = operand2 % 9;
    operand1 = operand1 | (machine.cpu.flagsRegister.getCf() << 8);
    result = (operand1 << operand2) | (operand1 >> (9 - operand2));
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result << 8, machine.cpu.flagsRegister.result,
                                         FlagsRegister::RCL | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRcr:
    operand2 = operand2 % 9;
    operand1 = operand1 | (machine.cpu.flagsRegister.getCf() << 8);
    result = (operand1 >> operand2) | (operand1 << (9 - operand2));
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result << 8, machine.cpu.flagsRegister.result,
                                         FlagsRegister::RCR | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opShl:
    result = operand1 << operand2;
    operand1 = operand1 << (operand2 - 1);
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SHL8);
opShr:
    result = operand1 >> operand2;
    operand1 = operand1 >> (operand2 - 1);
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SHR8);
opSar:
    operand1 = ((0 - (operand1 >> 7)) << 8) | operand1;
    result = operand1 >> operand2;
    operand1 = operand1 >> (operand2 - 1);
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SHR8);
}

inline void Interpreter::interpretBitGrp16(Instruction *instruction) {
    static const void* jumpTable[] = {
        &&opRol, &&opRor, &&opRcl, &&opRcr, &&opShl, &&opShr, &&opShl, &&opSar
    };

    goto *jumpTable[instruction->reg];

opRol:
    operand2 = operand2 % 16;
    result = (operand1 << operand2) | (operand1 >> (16 - operand2));
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result, machine.cpu.flagsRegister.result,
                                         FlagsRegister::ROL | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRor:
    operand2 = operand2 % 16;
    result = (operand1 >> operand2) | (operand1 << (16 - operand2));
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result, machine.cpu.flagsRegister.result,
                                         FlagsRegister::ROR | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRcl:
    operand2 = operand2 % 17;
    operand1 = operand1 | (machine.cpu.flagsRegister.getCf() << 16);
    result = (operand1 << operand2) | (operand1 >> (19 - operand2));
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result, machine.cpu.flagsRegister.result,
                                         FlagsRegister::RCL | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRcr:
    operand2 = operand2 % 17;
    operand1 = operand1 | (machine.cpu.flagsRegister.getCf() << 16);
    result = (operand1 >> operand2) | (operand1 << (19 - operand2));
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result, machine.cpu.flagsRegister.result,
                                         FlagsRegister::RCR | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opShl:
    result = operand1 << operand2;
    operand1 = operand1 << (operand2 - 1);
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SHL16);
opShr:
    result = operand1 >> operand2;
    operand1 = operand1 >> (operand2 - 1);
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SHR16);
opSar:
    operand1 = ((0 - (operand1 >> 15)) << 16) | operand1;
    result = operand1 >> operand2;
    operand1 = operand1 >> (operand2 - 1);
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SHR16);
}

inline void Interpreter::interpret(Instruction* instruction) {
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
        /*0x80*/ &&opGrpRmbIb, &&opGrpRmwIw, &&opGrpRmbIb, &&opGrpRmwIb, &&opTestRmbRb, &&opTestRmwRw, &&opXchgRmbRb, &&opXchgRmwRw,
        /*0x88*/ &&opMovRmbRb, &&opMovRmwRw, &&opMovRbRmb, &&opMovRwRmw, &&opMovRmwSr, &&opLea, &&opMovSrRmw, &&opPopRmw,
        /*0x90*/ &&opNop, &&opXchgEcxEax, &&opXchgEdxEax, &&opXchgEbxEax, &&opXchgEspEax, &&opXchgEbpEax, &&opXchgEsiEax, &&opXchgEdiEax,
        /*0x98*/ &&opCbw, &&opCwd, &&opCall, &&opWait, &&opPushF, &&opPopF, &&opSahF, &&opLahF,
        /*0xA0*/ &&opMovAlRmb, &&opMovAxRmw, &&opMovRmbAl, &&opMovRmwAx, &&opMovsb, &&opMovsw, &&opCmpsb, &&opCmpsw,
        /*0xA8*/ &&opTestAlIb, &&opTestAxIw, &&opStosb, &&opStosw, &&opLodsb, &&opLodsw, &&opScasb, &&opScasw,
        /*0xB0*/ &&opMovAlIb, &&opMovClIb, &&opMovDlIb, &&opMovBlIb, &&opMovAhIb, &&opMovChIb, &&opMovDhIb, &&opMovBhIb,
        /*0xB8*/ &&opMovEaxIw, &&opMovEcxIw, &&opMovEdxIw, &&opMovEbxIw, &&opMovEspIw, &&opMovEbpIw, &&opMovEsiIw, &&opMovEdiIw,
        /*0xC0*/ &&opGrpRmbIb2, &&opGrpRmwIb2, &&opRetIw, &&opRet, &&opLes, &&opLds, &&opMovRmbIb, &&opMovRmwIw,
        /*0xC8*/ &&opEnter, &&opLeave, &&opRetfIw, &&opRetf, &&opInt3, &&opIntIb, &&opInto, &&opIret,
        /*0xD0*/ &&opGrpRmb1, &&opGrpRmw1, &&opGrpRmbCl, &&opGrpRmwCl, &&opAam, &&opAad, &&opXlat, &&opXlat2,
        /*0xD8*/ &&error, &&error, &&error, &&error, &&error, &&error, &&error, &&error,
        /*0xE0*/ &&opLoopnz, &&opLoopz, &&opLoop, &&opJcxz, &&opInAlIb, &&opEaxIb, &&opOutIbAl, &&opOutIbEax,
        /*0xE8*/ &&opCallIw, &&opJmp, &&opJmpFar, &&opJmpShort, &&opInAlEdx, &&opInEaxEdx, &&opOutEdxAl, &&opOutEdxEax,
        /*0xF0*/ &&opLock, &&error, &&error, &&error, &&opHlt, &&opCmc, &&opGrpIb3, &&opGrpIw3
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
opInsb: return interpretInsb(instruction);
opInsw: return interpretInsw(instruction);
opOutsb: return interpretOutsb(instruction);
opOutsw: return interpretOutsw(instruction);

opJo: return interpretJo(instruction);
opJno: return interpretJno(instruction);
opJb: return interpretJb(instruction);
opJnb: return interpretJnb(instruction);
opJz: return interpretJz(instruction);
opJnz: return interpretJnz(instruction);
opJbe: return interpretJbe(instruction);
opJa: return interpretJa(instruction);
opJs: return interpretJs(instruction);
opJns: return interpretJns(instruction);
opJpe: return interpretJpe(instruction);
opJpo: return interpretJpo(instruction);
opJl: return interpretJl(instruction);
opJge: return interpretJge(instruction);
opJle: return interpretJle(instruction);
opJg: return interpretJg(instruction);

opGrpRmbIb: return interpretGrpRmbIb(instruction);
opGrpRmwIw: return interpretGrpRmwIw(instruction);
opGrpRmwIb: return interpretGrpRmwIb(instruction);
opTestRmbRb: return interpretTestRmbRb(instruction);
opTestRmwRw: return interpretTestRmwRw(instruction);
opXchgRmbRb: return interpretXchgRmbRb(instruction);
opXchgRmwRw: return interpretXchgRmwRw(instruction);

opMovRmbRb: return interpretMovRmbRb(instruction);
opMovRmwRw: return interpretMovRmwRw(instruction);
opMovRbRmb: return interpretMovRbRmb(instruction);
opMovRwRmw: return interpretMovRwRmw(instruction);
opMovRmwSr: return interpretMovRmwSr(instruction);
opLea: return interpretLea(instruction);
opMovSrRmw: return interpretMovSrRmw(instruction);
opPopRmw: return interpretPopRmw(instruction);

opNop: return;
opXchgEcxEax: return interpretXchgEcxEax();
opXchgEdxEax: return interpretXchgEdxEax();
opXchgEbxEax: return interpretXchgEbxEax();
opXchgEspEax: return interpretXchgEspEax();
opXchgEbpEax: return interpretXchgEbpEax();
opXchgEsiEax: return interpretXchgEsiEax();
opXchgEdiEax: return interpretXchgEdiEax();

opCbw: return interpretCbw();
opCwd: return interpretCwd();
opCall: return interpretCall(instruction);
opWait: return interpretWait();
opPushF: return interpretPushF();
opPopF: return interpretPopF();
opSahF: return interpretSahF();
opLahF: return interpretLahF();

opMovAlRmb: return interpretMovAlRmb(instruction);
opMovAxRmw: return interpretMovAxRmw(instruction);
opMovRmbAl: return interpretMovRmbAl(instruction);
opMovRmwAx: return interpretMovRmwAx(instruction);
opMovsb: return interpretMovsb(instruction);
opMovsw: return interpretMovsw(instruction);
opCmpsb: return interpretCmpsb(instruction);
opCmpsw: return interpretCmpsw(instruction);

opTestAlIb: return interpretTestAlIb(instruction);
opTestAxIw: return interpretTestAxIw(instruction);
opStosb: return interpretStosb(instruction);
opStosw: return interpretStosw(instruction);
opLodsb: return interpretLodsb(instruction);
opLodsw: return interpretLodsw(instruction);
opScasb: return interpretScasb(instruction);
opScasw: return interpretScasw(instruction);

opMovAlIb: return interpretMovAlIb(instruction);
opMovClIb: return interpretMovClIb(instruction);
opMovDlIb: return interpretMovDlIb(instruction);
opMovBlIb: return interpretMovBlIb(instruction);
opMovAhIb: return interpretMovAhIb(instruction);
opMovChIb: return interpretMovChIb(instruction);
opMovDhIb: return interpretMovDhIb(instruction);
opMovBhIb: return interpretMovBhIb(instruction);
opMovEaxIw: return interpretMovEaxIw(instruction);
opMovEcxIw: return interpretMovEcxIw(instruction);
opMovEdxIw: return interpretMovEdxIw(instruction);
opMovEbxIw: return interpretMovEbxIw(instruction);
opMovEspIw: return interpretMovEspIw(instruction);
opMovEbpIw: return interpretMovEbpIw(instruction);
opMovEsiIw: return interpretMovEsiIw(instruction);
opMovEdiIw: return interpretMovEdiIw(instruction);

opGrpRmbIb2: return interpretGrpRmbIb2(instruction);
opGrpRmwIb2: return interpretGrpRmwIb2(instruction);
opRetIw: return interpretRetIw(instruction);
opRet: return interpretRet(instruction);
opLes: return interpretLes(instruction);
opLds: return interpretLds(instruction);
opMovRmbIb: return interpretMovRmbIb(instruction);
opMovRmwIw: return interpretMovRmwIw(instruction);

opEnter: return interpretEnter(instruction);
opLeave: return interpretLeave();
opRetfIw: return interpretRetfIw(instruction);
opRetf: return interpretRetf(instruction);
opInt3: return interpretInt3();
opIntIb: return interpretIntIb(instruction);
opInto: return interpretInto();
opIret: return interpretIret(instruction);

opGrpRmb1: return interpretGrpRmb1(instruction);
opGrpRmw1: return interpretGrpRmw1(instruction);
opGrpRmbCl: return interpretGrpRmbCl(instruction);
opGrpRmwCl: return interpretGrpRmwCl(instruction);
opAam: return interpretAam(instruction);
opAad: return interpretAad(instruction);
opXlat: return interpretXlat();
opXlat2: return interpretXlat2(instruction);

opLoopnz: return interpretLoopnz(instruction);
opLoopz: return interpretLoopz(instruction);
opLoop: return interpretLoop(instruction);
opJcxz: return interpretJcxz(instruction);
opInAlIb: return interpretInAlIb(instruction);
opEaxIb: return interpretInEaxIb(instruction);
opOutIbAl:return interpretOutIbAl(instruction);
opOutIbEax: return interpretOutIbEax(instruction);

opCallIw: return interpretCallIw(instruction);
opJmp: return interpretJmp(instruction);
opJmpFar: return interpretJmpFar(instruction);
opJmpShort: return interpretJmpShort(instruction);
opInAlEdx: return interpretInAlEdx();
opInEaxEdx: return interpretInEaxEdx();
opOutEdxAl: return interpretOutEdxAl();
opOutEdxEax: return interpretOutEdxEax();

opLock: return interpretLock();
opHlt: return interpretHlt();
opCmc: return interpretCmc();
opGrpIb3: return interpretGrpIb3(instruction);
opGrpIw3: return interpretGrpIw3(instruction);

error:
    ERR("invalid opcode used: %d", instruction->opcode);
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
    operand2 = *WORD(operand2Address);

    result = operand1 + operand2;
    *WORD(operand2Address) = result;

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
    operand2 = *WORD(operand2Address);

    result = operand1 + operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD16);
}

inline void Interpreter::interpretAddAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 + operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
}

inline void Interpreter::interpretAddAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

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
    operand2 = *WORD(operand2Address);

    result = operand1 | operand2;
    *WORD(operand2Address) = result;

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
    operand2 = *WORD(operand2Address);

    result = operand1 | operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretOrAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 | operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretOrAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

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
    operand2 = *WORD(operand2Address);

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *WORD(operand2Address) = result;

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
    operand2 = *WORD(operand2Address);

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC16);
}

inline void Interpreter::interpretAdcAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
}

inline void Interpreter::interpretAdcAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

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

    operand1 = *WORD(operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *WORD(operand2Address) = result;

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
    operand2 = *WORD(operand2Address);

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB16);
}

inline void Interpreter::interpretSbbAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
}

inline void Interpreter::interpretSbbAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

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

    operand1 = *WORD(operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 & operand2;
    *WORD(operand2Address) = result;

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
    operand2 = *WORD(operand2Address);

    result = operand1 & operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretAndAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 & operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretAndAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

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

    operand1 = *WORD(operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 - operand2;
    *WORD(operand2Address) = result;

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
    operand2 = *WORD(operand2Address);

    result = operand1 - operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

inline void Interpreter::interpretSubAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 - operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

inline void Interpreter::interpretSubAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

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

    operand1 = *WORD(operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 ^ operand2;
    *WORD(operand2Address) = result;

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
    operand2 = *WORD(operand2Address);

    result = operand1 ^ operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretXorAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 ^ operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretXorAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

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

    operand1 = *WORD(operand2Address);
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
    operand2 = *WORD(operand2Address);

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

inline void Interpreter::interpretCmpAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

inline void Interpreter::interpretCmpAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

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
    lowerBound = *WORD(operand2Address);
    upperBound = *(WORD(operand2Address) + 1);

    if(index < lowerBound || index > (upperBound + 2)) {
        machine.cpu.interruptHandler->call(5);
    }
}

inline void Interpreter::interpretImulIw(Instruction *instruction) {
    static int32_t tempResult;

    decodeAddress16(instruction);

    operand1 = *WORD(operand2Address);
    operand2 = instruction->immediate;

    tempResult = operand1 * operand2;

    machine.cpu.registerTable[instruction->reg]->data = tempResult;

    machine.cpu.flagsRegister.set(tempResult >> 16, FlagsRegister::IMUL16);
}

inline void Interpreter::interpretPushIw(Instruction *instruction) {
    push(instruction->immediate);
}

inline void Interpreter::interpretImulIb(Instruction *instruction) {
    static int32_t tempResult;

    decodeAddress8(instruction);

    operand1 = *WORD(operand2Address);
    operand2 = instruction->immediate;

    tempResult = operand1 * operand2;

    machine.cpu.registerTable[instruction->reg]->data = tempResult;

    machine.cpu.flagsRegister.set(tempResult >> 16, FlagsRegister::IMUL8);
}

inline void Interpreter::interpretPushIb(Instruction *instruction) {
    push(instruction->immediate);
}

inline void Interpreter::interpretInsb(Instruction* instruction) {
    LOW(machine.cpu.ax.data) = machine.portHandler.in8(machine.cpu.dx.data);

    processLoop(instruction, 1);
}

inline void Interpreter::interpretInsw(Instruction* instruction) {
    machine.cpu.ax.data = machine.portHandler.in16(machine.cpu.dx.data);

    processLoop(instruction, 2);
}

inline void Interpreter::interpretOutsb(Instruction* instruction) {
    machine.portHandler.out8(machine.cpu.dx.data, LOW(machine.cpu.ax.data));

    processLoop(instruction, 1);
}

inline void Interpreter::interpretOutsw(Instruction* instruction) {
    machine.portHandler.out16(machine.cpu.dx.data, machine.cpu.ax.data);

    processLoop(instruction, 2);
}

inline void Interpreter::interpretJo(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJno(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJb(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getCf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}
inline void Interpreter::interpretJnb(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getCf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJz(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJnz(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJbe(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getCf() || machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJa(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getCf() && !machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJs(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getSf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJns(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getSf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJpe(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getPf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJpo(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getPf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJl(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getSf() != machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJge(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getSf() == machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJle(Instruction *instruction) {
    if((machine.cpu.flagsRegister.getSf() != machine.cpu.flagsRegister.getOf()) || machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretJg(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getZf() && (machine.cpu.flagsRegister.getOf() == machine.cpu.flagsRegister.getSf())) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

inline void Interpreter::interpretGrpRmbIb(Instruction *instruction) {
    static const void* jumpTable[] = {
        &&opAdd, &&opOr, &&opAdc, &&opSbb, &&opAnd8, &&opSub8, &&opXor8, &&opFlagSub
    };

    decodeAddress8(instruction);

    operand1 = *operand2Address;
    operand2 = instruction->immediate;

    goto *jumpTable[instruction->reg];

opAdd:
    result = operand1 + operand2;
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
opOr:
    result = operand1 | operand2;
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opAdc:
    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
opSbb:
    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
opAnd8:
    result = operand1 & operand2;
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opSub8:
    result = operand1 - operand2;
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
opXor8:
    result = operand1 ^ operand2;
    *operand2Address = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opFlagSub:
    result = operand1 - operand2;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

inline void Interpreter::interpretGrpRmwIw(Instruction *instruction) {
    static const void* jumpTable[] = {
        &&opAdd, &&opOr, &&opAdc, &&opSbb, &&opAnd8, &&opSub8, &&opXor8, &&opFlagSub
    };

    decodeAddress8(instruction);

    operand1 = *WORD(operand2Address);
    operand2 = instruction->immediate;

    goto *jumpTable[instruction->reg];

opAdd:
    result = operand1 + operand2;
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
opOr:
    result = operand1 | operand2;
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opAdc:
    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
opSbb:
    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
opAnd8:
    result = operand1 & operand2;
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opSub8:
    result = operand1 - operand2;
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
opXor8:
    result = operand1 ^ operand2;
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opFlagSub:
    result = operand1 - operand2;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}


inline void Interpreter::interpretGrpRmwIb(Instruction *instruction) {
    static const void* jumpTable[] = {
        &&opAdd, &&opOr, &&opAdc, &&opSbb, &&opAnd8, &&opSub8, &&opXor8, &&opFlagSub
    };

    decodeAddress8(instruction);

    operand1 = *WORD(operand2Address);
    operand2 = instruction->immediate;

    goto *jumpTable[instruction->reg];

opAdd:
    result = operand1 + operand2;
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
opOr:
    result = operand1 | operand2;
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opAdc:
    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
opSbb:
    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
opAnd8:
    result = operand1 & operand2;
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opSub8:
    result = operand1 - operand2;
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
opXor8:
    result = operand1 ^ operand2;
    *WORD(operand2Address) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opFlagSub:
    result = operand1 - operand2;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

inline void Interpreter::interpretTestRmbRb(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *operand2Address;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 & operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretTestRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *WORD(operand2Address);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 & operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretXchgRmbRb(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *operand2Address;
    *operand2Address = *machine.cpu.registerAddressTable[instruction->reg];
    *machine.cpu.registerAddressTable[instruction->reg] = operand1;
}

inline void Interpreter::interpretXchgRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *WORD(operand2Address);
    *WORD(operand2Address) = machine.cpu.registerTable[instruction->reg]->data;
    machine.cpu.registerTable[instruction->reg]->data = operand1;
}

inline void Interpreter::interpretMovRmbRb(Instruction *instruction) {
    decodeAddress16(instruction);

    *operand2Address = *machine.cpu.registerAddressTable[instruction->reg];
}

inline void Interpreter::interpretMovRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    *WORD(operand2Address) = machine.cpu.registerTable[instruction->reg]->data;
}

inline void Interpreter::interpretMovRbRmb(Instruction *instruction) {
    decodeAddress16(instruction);

    *machine.cpu.registerAddressTable[instruction->reg] = *operand2Address;
}

inline void Interpreter::interpretMovRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    machine.cpu.registerTable[instruction->reg]->data = *WORD(operand2Address);
}

inline void Interpreter::interpretMovRmwSr(Instruction *instruction) {
    decodeAddress16(instruction);

    *WORD(operand2Address) = machine.cpu.segmentRegisterTable[instruction->reg]->data;
}

inline void Interpreter::interpretLea(Instruction *instruction) {
    decodeAddress16(instruction);

    machine.cpu.registerTable[instruction->reg]->data = decodeRelativeAddress(instruction);
}

inline void Interpreter::interpretMovSrRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    machine.cpu.segmentRegisterTable[instruction->reg]->data = *WORD(operand2Address);
}

inline void Interpreter::interpretPopRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    *WORD(operand2Address) = pop();
}

inline void Interpreter::interpretXchgEcxEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.cx.data;
    machine.cpu.cx.data = operand1;
}

inline void Interpreter::interpretXchgEdxEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.dx.data;
    machine.cpu.dx.data = operand1;
}

inline void Interpreter::interpretXchgEbxEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.bx.data;
    machine.cpu.bx.data = operand1;
}

inline void Interpreter::interpretXchgEspEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.sp.data;
    machine.cpu.sp.data = operand1;
}

inline void Interpreter::interpretXchgEbpEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.bp.data;
    machine.cpu.bp.data = operand1;
}

inline void Interpreter::interpretXchgEsiEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.si.data;
    machine.cpu.si.data = operand1;
}

inline void Interpreter::interpretXchgEdiEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.di.data;
    machine.cpu.di.data = operand1;
}

inline void Interpreter::interpretCbw(){
    *machine.cpu.registerAddressTable[machine.cpu.AH] = 0 - ((*machine.cpu.registerAddressTable[machine.cpu.AL]) >> 7);
}

inline void Interpreter::interpretCwd(){
    machine.cpu.dx.data = 0 - ((*machine.cpu.registerAddressTable[machine.cpu.AH]) >> 7);
}

inline void Interpreter::interpretCall(Instruction *instruction){
    push(machine.cpu.cs.data);
    push(machine.cpu.ip.data + instruction->length);

    /*instruction length is always added after interpreter return*/
    machine.cpu.ip.data = instruction->immediate - instruction->length;
    machine.cpu.cs.data = instruction->displacement;
}

inline void Interpreter::interpretWait(){
    //señor nada
}

inline void Interpreter::interpretPushF(){
    operand1 =
            (uint16_t)machine.cpu.flagsRegister.getCf() |
            ((uint16_t)machine.cpu.flagsRegister.getPf() << 2) |
            ((uint16_t)machine.cpu.flagsRegister.getAf() << 4) |
            ((uint16_t)machine.cpu.flagsRegister.getZf() << 6) |
            ((uint16_t)machine.cpu.flagsRegister.getSf() << 7) |
            ((uint16_t)machine.cpu.flagsRegister.tf << 8) |
            ((uint16_t)machine.cpu.flagsRegister.itf << 9) |
            ((uint16_t)machine.cpu.flagsRegister.df << 10) |
            ((uint16_t)machine.cpu.flagsRegister.getOf() << 11);

    push(operand1);
}

inline void Interpreter::interpretPopF(){
    static const uint16_t resultTable[] = {
        0, 0, 0, 2,
        0, 0, 0x8000, 0x8002
    };

    operand1 = pop();

    machine.cpu.flagsRegister.tf = (operand1 & 256 /*1 << 8*/) != 0;
    machine.cpu.flagsRegister.itf = (operand1 & 512 /*1 << 9*/) != 0;
    machine.cpu.flagsRegister.df = (operand1 & 1024 /*1 << 10*/) != 0;

    /*00 01 02*/
    /*PF ZF SF*/
    operand2 =
            ((operand1 & 4 /*1 << 2*/ ) >> 2) |
            ((operand1 & 64 /*1 << 6*/ ) >> 5) |
            ((operand1 & 128 /*1 << 7*/ ) >> 5);

    result = resultTable[operand2];

    machine.cpu.flagsRegister.set(operand1, 0, result, FlagsRegister::POPF16);
}

inline void Interpreter::interpretSahF(){
    static const uint16_t resultTable[] = {
        0, 0, 0, 2,
        0, 0, 0x8000, 0x8002
    };

    operand1 = *machine.cpu.registerAddressTable[machine.cpu.AH];

    /*00 01 02*/
    /*PF ZF SF*/
    operand2 =
            ((operand1 & 4 /*1 << 2*/ ) >> 2) |
            ((operand1 & 64 /*1 << 6*/ ) >> 5) |
            ((operand1 & 128 /*1 << 7*/ ) >> 5);

    result = resultTable[operand2];

    machine.cpu.flagsRegister.set(operand1, 0, result, FlagsRegister::POPF16);
}

inline void Interpreter::interpretLahF(){
    *machine.cpu.registerAddressTable[machine.cpu.AH] =
            (uint16_t)machine.cpu.flagsRegister.getCf() |
            ((uint16_t)machine.cpu.flagsRegister.getPf() << 2) |
            ((uint16_t)machine.cpu.flagsRegister.getAf() << 4) |
            ((uint16_t)machine.cpu.flagsRegister.getZf() << 6) |
            ((uint16_t)machine.cpu.flagsRegister.getSf() << 7);
}

inline void Interpreter::interpretMovAlRmb(Instruction *instruction) {
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + instruction->immediate;
    LOW(machine.cpu.ax.data) = machine.ram.buffer[operand1];
}

inline void Interpreter::interpretMovAxRmw(Instruction *instruction) {
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + instruction->immediate;
    machine.cpu.ax.data = *WORD(&machine.ram.buffer[operand1]);
}


inline void Interpreter::interpretMovRmbAl(Instruction *instruction) {
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + instruction->immediate;
    machine.ram.buffer[operand1] = LOW(machine.cpu.ax.data);
}

inline void Interpreter::interpretMovRmwAx(Instruction *instruction) {
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + instruction->immediate;
    *WORD(&machine.ram.buffer[operand1]) = machine.cpu.ax.data;
}

inline void Interpreter::interpretMovsb(Instruction *instruction) {
    /*source address*/
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + machine.cpu.si.data;
    /*destination address*/
    operand2 = (machine.cpu.es.data << 4) + machine.cpu.di.data;

    machine.ram.buffer[operand2] = machine.ram.buffer[operand1];

    processLoop(instruction, 1);
}


inline void Interpreter::interpretMovsw(Instruction *instruction) {
    /*source address*/
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + machine.cpu.si.data;
    /*destination address*/
    operand2 = (machine.cpu.es.data << 4) + machine.cpu.di.data;

    machine.ram.buffer[operand2] = machine.ram.buffer[operand1];
    machine.ram.buffer[operand2 + 1] = machine.ram.buffer[operand1 + 1];

    processLoop(instruction, 2);
}


inline void Interpreter::interpretCmpsb(Instruction *instruction) {
    /*source value*/
    operand1 = machine.ram.buffer[(decodeBaseRegisterValue(instruction) << 4) + machine.cpu.si.data];
    /*destination value*/
    operand2 = machine.ram.buffer[(machine.cpu.es.data << 4) + machine.cpu.di.data];

    result = operand1 - operand2;
    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);

    processLoop(instruction, 1);
}


inline void Interpreter::interpretCmpsw(Instruction *instruction) {
    /*source value*/
    operand1 = *WORD(&machine.ram.buffer[(decodeBaseRegisterValue(instruction) << 4) + machine.cpu.si.data]);
    /*destination value*/
    operand2 = *WORD(&machine.ram.buffer[(machine.cpu.es.data << 4) + machine.cpu.di.data]);

    result = operand1 - operand2;
    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);

    processLoop(instruction, 2);
}

inline void Interpreter::interpretTestAlIb(Instruction *instruction) {
    operand1 = LOW(machine.cpu.ax.data);
    operand2 = instruction->immediate;
    result = operand1 & operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

inline void Interpreter::interpretTestAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;
    result = operand1 & operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

inline void Interpreter::interpretStosb(Instruction* instruction) {
    machine.ram.buffer[(machine.cpu.es.data << 4) + machine.cpu.di.data]
            = LOW(machine.cpu.ax.data);

    if(machine.cpu.flagsRegister.df) {
        machine.cpu.di.data -= 1;
    } else {
        machine.cpu.di.data += 1;
    }

    if(!isLoopFinished(instruction)) {
        machine.cpu.cx.data -= 1;
        machine.cpu.ip.data -= instruction->length;
    }
}

inline void Interpreter::interpretStosw(Instruction* instruction) {
    *WORD(&machine.ram.buffer[(machine.cpu.es.data << 4) + machine.cpu.di.data])
            = machine.cpu.ax.data;

    if(machine.cpu.flagsRegister.df) {
        machine.cpu.di.data -= 2;
    } else {
        machine.cpu.di.data += 2;
    }

    if(!isLoopFinished(instruction)) {
        machine.cpu.cx.data -= 1;
        machine.cpu.ip.data -= instruction->length;
    }
}

inline void Interpreter::interpretLodsb(Instruction* instruction) {
    LOW(machine.cpu.ax.data)
            = machine.ram.buffer[(decodeBaseRegisterValue(instruction) << 4) + machine.cpu.si.data];

    if(machine.cpu.flagsRegister.df) {
        machine.cpu.si.data -= 1;
    } else {
        machine.cpu.si.data += 1;
    }

    if(!isLoopFinished(instruction)) {
        machine.cpu.cx.data -= 1;
        machine.cpu.ip.data -= instruction->length;
    }
}

inline void Interpreter::interpretLodsw(Instruction* instruction) {
    machine.cpu.ax.data
            = *WORD(&machine.ram.buffer[(decodeBaseRegisterValue(instruction) << 4) + machine.cpu.si.data]);

    if(machine.cpu.flagsRegister.df) {
        machine.cpu.si.data -= 2;
    } else {
        machine.cpu.si.data += 2;
    }

    if(!isLoopFinished(instruction)) {
        machine.cpu.cx.data -= 1;
        machine.cpu.ip.data -= instruction->length;
    }
}

inline void Interpreter::interpretScasb(Instruction* instruction) {
    operand1 = LOW(machine.cpu.ax.data);
    operand2 = machine.ram.buffer[(machine.cpu.es.data << 4) + machine.cpu.di.data];
    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);

    if(machine.cpu.flagsRegister.df) {
        machine.cpu.di.data -= 1;
    } else {
        machine.cpu.di.data += 1;
    }

    if(!isLoopFinished(instruction)) {
        machine.cpu.cx.data -= 1;
        machine.cpu.ip.data -= instruction->length;
    }
}

inline void Interpreter::interpretScasw(Instruction* instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = *WORD(&machine.ram.buffer[(machine.cpu.es.data << 4) + machine.cpu.di.data]);
    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);

    if(machine.cpu.flagsRegister.df) {
        machine.cpu.di.data -= 2;
    } else {
        machine.cpu.di.data += 2;
    }

    if(!isLoopFinished(instruction)) {
        machine.cpu.cx.data -= 1;
        machine.cpu.ip.data -= instruction->length;
    }
}

inline void Interpreter::interpretMovAlIb(Instruction* instruction){
    LOW(machine.cpu.ax.data) = instruction->immediate;
}

inline void Interpreter::interpretMovClIb(Instruction* instruction){
    LOW(machine.cpu.cx.data) = instruction->immediate;
}

inline void Interpreter::interpretMovDlIb(Instruction* instruction){
    LOW(machine.cpu.dx.data) = instruction->immediate;
}

inline void Interpreter::interpretMovBlIb(Instruction* instruction){
    LOW(machine.cpu.bx.data) = instruction->immediate;
}

inline void Interpreter::interpretMovAhIb(Instruction* instruction){
    HIGH(machine.cpu.ax.data) = instruction->immediate;
}

inline void Interpreter::interpretMovChIb(Instruction* instruction){
    HIGH(machine.cpu.cx.data) = instruction->immediate;
}

inline void Interpreter::interpretMovDhIb(Instruction* instruction){
    HIGH(machine.cpu.dx.data) = instruction->immediate;
}

inline void Interpreter::interpretMovBhIb(Instruction* instruction){
    HIGH(machine.cpu.bx.data) = instruction->immediate;
}

inline void Interpreter::interpretMovEaxIw(Instruction* instruction){
    machine.cpu.ax.data = instruction->immediate;
}

inline void Interpreter::interpretMovEcxIw(Instruction* instruction){
    machine.cpu.cx.data = instruction->immediate;
}

inline void Interpreter::interpretMovEdxIw(Instruction* instruction){
    machine.cpu.dx.data = instruction->immediate;
}

inline void Interpreter::interpretMovEbxIw(Instruction* instruction){
    machine.cpu.bx.data = instruction->immediate;
}

inline void Interpreter::interpretMovEspIw(Instruction* instruction){
    machine.cpu.sp.data = instruction->immediate;
}

inline void Interpreter::interpretMovEbpIw(Instruction* instruction){
    machine.cpu.bp.data = instruction->immediate;
}

inline void Interpreter::interpretMovEsiIw(Instruction* instruction){
    machine.cpu.si.data = instruction->immediate;
}

inline void Interpreter::interpretMovEdiIw(Instruction* instruction){
    machine.cpu.di.data = instruction->immediate;
}

inline void Interpreter::interpretGrpRmbIb2(Instruction *instruction) {
    decodeAddress8(instruction);

    /*value*/
    operand1 = *operand2Address;
    /*how many time*/
    operand2 = instruction->immediate & 0x1F;

    /*for 0 shifts or rotates, the flags should be unaffected*/
    if(!operand2) {
        return;
    }

    interpretBitGrp8(instruction);
}

inline void Interpreter::interpretGrpRmwIb2(Instruction *instruction) {
    decodeAddress16(instruction);

    /*value*/
    operand1 = *WORD(operand2Address);
    /*how many time*/
    operand2 = instruction->immediate & 0x1F;

    /*for 0 shifts or rotates, the flags should be unaffected*/
    if(!operand2) {
        return;
    }

    interpretBitGrp16(instruction);
}

inline void Interpreter::interpretRetIw(Instruction *instruction) {
    /*instruction length is always added after instruction interpret*/
    machine.cpu.ip.data = pop() - instruction->length;
    machine.cpu.sp.data += instruction->immediate;
}

inline void Interpreter::interpretRet(Instruction* instruction) {
    /*instruction length is always added after instruction interpret*/
    machine.cpu.ip.data = pop() - instruction->length;
}

inline void Interpreter::interpretLes(Instruction *instruction) {
    decodeAddress16(instruction);
    machine.cpu.registerTable[instruction->reg]->data = *WORD(operand2Address);
    machine.cpu.es.data = *WORD(operand2Address + 2);
}

inline void Interpreter::interpretLds(Instruction *instruction) {
    decodeAddress16(instruction);
    machine.cpu.registerTable[instruction->reg]->data = *WORD(operand2Address);
    machine.cpu.ds.data = *WORD(operand2Address + 2);
}

inline void Interpreter::interpretMovRmbIb(Instruction* instruction){
    decodeAddress8(instruction);
    *operand2Address = instruction->immediate;
}

inline void Interpreter::interpretMovRmwIw(Instruction* instruction){
    decodeAddress16(instruction);
    *WORD(operand2Address) = instruction->immediate;
}

inline void Interpreter::interpretEnter(Instruction* instruction) {
    static uint32_t framePtr;
    static uint16_t stackSize;
    static uint8_t level;

    framePtr = machine.cpu.sp.data;
    stackSize = instruction->immediate;
    level = instruction->displacement;

    push(machine.cpu.bp.data);

    if (level) {
        while (--level) {
            machine.cpu.bp.data -= 2;
            push (*WORD(&machine.ram.buffer[machine.cpu.bp.data]));
        }

        push (framePtr);
    }

    machine.cpu.bp.data = framePtr;
    machine.cpu.sp.data -= stackSize;
}

inline void Interpreter::interpretLeave() {
    machine.cpu.sp.data = machine.cpu.bp.data;
    machine.cpu.bp.data = pop();
}

inline void Interpreter::interpretRetfIw(Instruction* instruction) {
    /*instruction length is always added after instruction interpret*/
    machine.cpu.ip.data = pop() - instruction->length;
    machine.cpu.cs.data = pop();
    machine.cpu.sp.data += instruction->immediate;
}

inline void Interpreter::interpretRetf(Instruction* instruction) {
    /*instruction length is always added after instruction interpret*/
    machine.cpu.ip.data = pop() - instruction->length;
    machine.cpu.cs.data = pop();
}

inline void Interpreter::interpretInt3() {
    machine.cpu.interruptHandler->call(3);
}

inline void Interpreter::interpretIntIb(Instruction* instruction) {
    machine.cpu.interruptHandler->call(instruction->immediate);
}

inline void Interpreter::interpretInto() {
    if(machine.cpu.flagsRegister.getOf()) {
        machine.cpu.interruptHandler->call(4);
    }
}

inline void Interpreter::interpretIret(Instruction* instruction) {
    /*instruction length is always added after instruction interpret*/
    machine.cpu.ip.data = pop() - instruction->length;
    machine.cpu.cs.data = pop();

    /*flags*/
    interpretPopF();
}

inline void Interpreter::interpretGrpRmb1(Instruction *instruction) {
    decodeAddress8(instruction);

    /*value*/
    operand1 = *operand2Address;
    /*how many time*/
    operand2 = 1;

    interpretBitGrp8(instruction);
}

inline void Interpreter::interpretGrpRmw1(Instruction *instruction) {
    decodeAddress16(instruction);

    /*value*/
    operand1 = *WORD(operand2Address);
    /*how many time*/
    operand2 = 1;

    interpretBitGrp16(instruction);
}

inline void Interpreter::interpretGrpRmbCl(Instruction *instruction) {
    decodeAddress8(instruction);

    /*value*/
    operand1 = *operand2Address;
    /*how many time*/
    operand2 = LOW(machine.cpu.cx.data);

    /*for 0 shifts or rotates, the flags should be unaffected*/
    if(!operand2) {
        return;
    }

    interpretBitGrp8(instruction);
}

inline void Interpreter::interpretGrpRmwCl(Instruction *instruction) {
    decodeAddress16(instruction);

    /*value*/
    operand1 = *WORD(operand2Address);
    /*how many time*/
    operand2 = LOW(machine.cpu.cx.data);

    /*for 0 shifts or rotates, the flags should be unaffected*/
    if(!operand2) {
        return;
    }

    interpretBitGrp16(instruction);
}

inline void Interpreter::interpretAam(Instruction *instruction) {
    if (!instruction->immediate) {
        machine.cpu.interruptHandler->call(0);
    } else {
        HIGH(machine.cpu.ax.data) = LOW(machine.cpu.ax.data) / instruction->immediate;
        LOW(machine.cpu.ax.data) = LOW(machine.cpu.ax.data) % instruction->immediate;
        /*instruction doesn't matter as only ZF, PF, SF are set*/
        machine.cpu.flagsRegister.set(machine.cpu.ax.data, FlagsRegister::IMUL16);
    }
}

inline void Interpreter::interpretAad(Instruction *instruction) {
    machine.cpu.ax.data = (HIGH(machine.cpu.ax.data) * instruction->immediate + LOW(machine.cpu.ax.data)) & 0xFF;
    /*instruction doesn't matter as only ZF, PF, SF are set*/
    machine.cpu.flagsRegister.set(machine.cpu.ax.data, FlagsRegister::IMUL16);
}

inline void Interpreter::interpretXlat() {
    /*I found this in the Fake86 implementation, but no mention in the intel manual*/
    if(machine.cpu.flagsRegister.getCf()) {
        LOW(machine.cpu.ax.data) = 0xFF;
    } else {
        LOW(machine.cpu.ax.data) = 0x00;
    }
}

inline void Interpreter::interpretXlat2(Instruction *instruction) {
    LOW(machine.cpu.ax.data) = (decodeBaseRegisterValue(instruction) << 4)
            + machine.cpu.bx.data + LOW(machine.cpu.ax.data);

}

inline void Interpreter::interpretLoopnz(Instruction *instruction) {
    machine.cpu.cx.data -= 1;

    if(machine.cpu.cx.data && !machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += SIGNED16(instruction->immediate);
    }
}

inline void Interpreter::interpretLoopz(Instruction *instruction) {
    machine.cpu.cx.data -= 1;

    if(machine.cpu.cx.data && machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += SIGNED16(instruction->immediate);
    }
}

inline void Interpreter::interpretLoop(Instruction *instruction) {
    machine.cpu.cx.data -= 1;

    if(machine.cpu.cx.data) {
        machine.cpu.ip.data += SIGNED16(instruction->immediate);
    }
}

inline void Interpreter::interpretJcxz(Instruction *instruction) {
    if(!machine.cpu.cx.data) {
        machine.cpu.ip.data += SIGNED16(instruction->immediate);
    }
}

inline void Interpreter::interpretInAlIb(Instruction *instruction) {
    LOW(machine.cpu.ax.data) = machine.portHandler.in8(instruction->immediate);
}

inline void Interpreter::interpretInEaxIb(Instruction *instruction) {
    machine.cpu.ax.data = machine.portHandler.in16(instruction->immediate);
}

inline void Interpreter::interpretOutIbAl(Instruction *instruction) {
    machine.portHandler.out8(instruction->immediate, LOW(machine.cpu.ax.data));
}

inline void Interpreter::interpretOutIbEax(Instruction *instruction) {
    machine.portHandler.out16(instruction->immediate, machine.cpu.ax.data);
}

inline void Interpreter::interpretCallIw(Instruction *instruction) {
    push(machine.cpu.ip.data + instruction->length);
    machine.cpu.ip.data += instruction->immediate;
}

inline void Interpreter::interpretJmp(Instruction *instruction) {
    machine.cpu.ip.data += instruction->immediate;
}

inline void Interpreter::interpretJmpFar(Instruction *instruction) {
    machine.cpu.ip.data = instruction->immediate;
    machine.cpu.cs.data = instruction->displacement;
}

inline void Interpreter::interpretJmpShort(Instruction *instruction) {
    machine.cpu.ip.data += SIGNED16(instruction->immediate);
}

inline void Interpreter::interpretInAlEdx() {
    LOW(machine.cpu.ax.data) = machine.portHandler.in8(machine.cpu.dx.data);
}

inline void Interpreter::interpretInEaxEdx() {
    machine.cpu.ax.data = machine.portHandler.in16(machine.cpu.dx.data);
}

inline void Interpreter::interpretOutEdxAl() {
    machine.portHandler.out8(machine.cpu.dx.data, LOW(machine.cpu.ax.data));
}

inline void Interpreter::interpretOutEdxEax() {
    machine.portHandler.out16(machine.cpu.dx.data, machine.cpu.ax.data);
}

inline void Interpreter::interpretLock() {
    //todo
}

inline void Interpreter::interpretHlt() {
    //todo
}

inline void Interpreter::interpretCmc() {
    machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf() | (machine.cpu.flagsRegister.getOf() << 1), !machine.cpu.flagsRegister.getCf(),
                                  machine.cpu.flagsRegister.result, FlagsRegister::CLC | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
}

inline void Interpreter::interpretGrpIb3(Instruction* instruction) {
    static void* jumpTable[] {
        &&opTest, &&opTest, &&opNot, &&opNeg, &&opMul, &&opIMul, &&opDiv, &&opIDiv,
    };
    static int32_t tmp;

    decodeAddress8(instruction);
    operand1 = *operand2Address;

    goto *jumpTable[instruction->reg];

opTest:
    machine.cpu.flagsRegister.set(operand1 & instruction->immediate, machine.cpu.flagsRegister.LOG8);
opNot:
    *operand2Address = ~operand1;
opNeg:
    *operand2Address = (~operand1) + 1;
    machine.cpu.flagsRegister.set(0, operand1, *operand2Address, machine.cpu.flagsRegister.NEG8);
opMul:
    machine.cpu.ax.data = LOW(machine.cpu.ax.data) * operand1;
    machine.cpu.flagsRegister.set(machine.cpu.ax.data, FlagsRegister::MUL8);
opIMul:
    machine.cpu.ax.data = SIGNED16(LOW(machine.cpu.ax.data)) * SIGNED16(operand1);
    machine.cpu.flagsRegister.set(machine.cpu.ax.data, FlagsRegister::IMUL8);
opDiv:
    if(operand1 == 0) {
        machine.cpu.interruptHandler->call(0);
    } else {
        operand2 = machine.cpu.ax.data / operand1;

        if(operand2 > 0xFF) {
            machine.cpu.interruptHandler->call(0);
        } else {
            LOW(machine.cpu.ax.data) = operand2;
            HIGH(machine.cpu.ax.data) = machine.cpu.ax.data % operand1;
        }
    }
opIDiv:
    if(operand1 == 0) {
        machine.cpu.interruptHandler->call(0);
    } else {
        tmp = SIGNED16(machine.cpu.ax.data) / SIGNED16(operand1);

        if(tmp > 0x7F || tmp < 0x80F) {
            machine.cpu.interruptHandler->call(0);
        } else {
            LOW(machine.cpu.ax.data) = tmp;
            HIGH(machine.cpu.ax.data) = SIGNED16(machine.cpu.ax.data) % SIGNED16(operand1);
        }
    }
}

inline void Interpreter::interpretGrpIw3(Instruction* instruction) {
}

#endif // INTERPRETER_H
