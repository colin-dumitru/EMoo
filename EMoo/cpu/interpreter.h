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
    Register16* baseRegisterTable_ds[Instruction::GS + 1];
    Register16* baseRegisterTable_ss[Instruction::GS + 1];
    /*it's a table of... base register tables. Used to decide if the default register is SS or DS*/
    Register16** baseRegisterTableTable[0b1001 /*0x0000 is the ZERO register*/];

    InstructionCache cache;

    uint32_t operand1;
    uint32_t operand2;
    uint32_t result;
    uint8_t* rmAddress;

    void decodeAddress8(Instruction* instruction);
    void decodeAddress16(Instruction* instruction);
    void decodeMemoryAddress(Instruction* instruction);

    uint16_t decodeBaseRegisterValue(Instruction* instruction);
    uint16_t decodeRelativeAddress(Instruction* instruction);

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
    void interpretRet();
    void interpretLes(Instruction* instruction);
    void interpretLds(Instruction* instruction);
    void interpretMovRmbIb(Instruction* instruction);
    void interpretMovRmwIw(Instruction* instruction);

    void interpretEnter(Instruction* instruction);
    void interpretLeave();
    void interpretRetfIw(Instruction* instruction);
    void interpretRetf();
    void interpretInt3();
    void interpretIntIb(Instruction* instruction);
    void interpretInto();
    void interpretIret();

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

    void interpretClc();
    void interpretStc();
    void interpretCli();
    void interpretSti();
    void interpretCld();
    void interpretStd();
    void interpretGrp4(Instruction* instruction);
    void interpretGrp5(Instruction* instruction);

public:
    Interpreter();
    ~Interpreter();

    void reset();

    void push(uint16_t value);
    uint16_t pop();

    void interpret(uint32_t address);
};

inline void Interpreter::decodeAddress8(Instruction *instruction) {
    if(instruction->registerAddressing) {
        rmAddress = machine.cpu.registerAddressTable[instruction->base];
    } else {
        decodeMemoryAddress(instruction);
    }
}

inline void Interpreter::decodeAddress16(Instruction *instruction) {
    if(instruction->registerAddressing) {
        rmAddress = (uint8_t*)&machine.cpu.registerTable[instruction->base]->data;
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

    rmAddress = &machine.ram.buffer[(baseRegisterValue << 4) + relativeAddress];
}

inline uint16_t Interpreter::decodeBaseRegisterValue(Instruction *instruction) {
    /*first get which register table to use (is the default DS or SS) and then get the actual register*/
    return baseRegisterTableTable[instruction->base][instruction->prefix & Instruction::OPERAND_MASK]->data;
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

inline void Interpreter::interpret(uint32_t address) {
    static FILE* out = fopen("/tmp/x86/mine", "w");

    if(!cache.cacheSet[address]) {
        cache.cacheSet[address] = true;
        machine.cpu.decoder->decode(address, &cache.instructionCache[address]);
    }
    machine.cpu.ip.data += cache.instructionCache[address].length;
    fprintf(out, "%x %x %x %x %x %x\n",
            machine.ram.buffer[address], machine.ram.buffer[address + 1], machine.ram.buffer[address + 2], machine.ram.buffer[address + 3], machine.cpu.bx.data, machine.ram.buffer[0x3e7]);
    interpret(&cache.instructionCache[address]);
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
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), (*rmAddress << 8) | *rmAddress, machine.cpu.flagsRegister.result,
                                         FlagsRegister::ROL | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRor:
    operand2 = operand2 % 8;
    result = (operand1 >> operand2) | (operand1 << (8 - operand2));
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), (*rmAddress << 8) | *rmAddress, machine.cpu.flagsRegister.result,
                                         FlagsRegister::ROR | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRcl:
    operand2 = operand2 % 9;
    operand1 = operand1 | (machine.cpu.flagsRegister.getCf() << 8);
    result = (operand1 << operand2) | (operand1 >> (9 - operand2));
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result << 8, machine.cpu.flagsRegister.result,
                                         FlagsRegister::RCL | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRcr:
    operand2 = operand2 % 9;
    operand1 = operand1 | (machine.cpu.flagsRegister.getCf() << 8);
    result = (operand1 >> operand2) | (operand1 << (9 - operand2));
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result << 8, machine.cpu.flagsRegister.result,
                                         FlagsRegister::RCR | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opShl:
    result = operand1 << operand2;
    operand1 = operand1 << (operand2 - 1);
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SHL8);
opShr:
    result = operand1 >> operand2;
    operand1 = operand1 >> (operand2 - 1);
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SHR8);
opSar:
    operand1 = ((0 - (operand1 >> 7)) << 8) | operand1;
    result = operand1 >> operand2;
    operand1 = operand1 >> (operand2 - 1);
    *rmAddress = result;
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
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result, machine.cpu.flagsRegister.result,
                                         FlagsRegister::ROL | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRor:
    operand2 = operand2 % 16;
    result = (operand1 >> operand2) | (operand1 << (16 - operand2));
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result, machine.cpu.flagsRegister.result,
                                         FlagsRegister::ROR | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRcl:
    operand2 = operand2 % 17;
    operand1 = operand1 | (machine.cpu.flagsRegister.getCf() << 16);
    result = (operand1 << operand2) | (operand1 >> (19 - operand2));
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result, machine.cpu.flagsRegister.result,
                                         FlagsRegister::RCL | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opRcr:
    operand2 = operand2 % 17;
    operand1 = operand1 | (machine.cpu.flagsRegister.getCf() << 16);
    result = (operand1 >> operand2) | (operand1 << (19 - operand2));
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), result, machine.cpu.flagsRegister.result,
                                         FlagsRegister::RCR | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
opShl:
    result = operand1 << operand2;
    operand1 = operand1 << (operand2 - 1);
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SHL16);
opShr:
    result = operand1 >> operand2;
    operand1 = operand1 >> (operand2 - 1);
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SHR16);
opSar:
    operand1 = ((0 - (operand1 >> 15)) << 16) | operand1;
    result = operand1 >> operand2;
    operand1 = operand1 >> (operand2 - 1);
    *WORD(rmAddress) = result;
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
        /*0xF0*/ &&opLock, &&error, &&error, &&error, &&opHlt, &&opCmc, &&opGrpIb3, &&opGrpIw3,
        /*0xF8*/ &&opClc, &&opStc, &&opCli, &&opSti, &&opCld, &&opStd, &&opGrp4, &&opGrp5
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
opRet: return interpretRet();
opLes: return interpretLes(instruction);
opLds: return interpretLds(instruction);
opMovRmbIb: return interpretMovRmbIb(instruction);
opMovRmwIw: return interpretMovRmwIw(instruction);

opEnter: return interpretEnter(instruction);
opLeave: return interpretLeave();
opRetfIw: return interpretRetfIw(instruction);
opRetf: return interpretRetf();
opInt3: return interpretInt3();
opIntIb: return interpretIntIb(instruction);
opInto: return interpretInto();
opIret: return interpretIret();

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

opClc: return interpretClc();
opStc: return interpretStc();
opCli: return interpretCli();
opSti: return interpretSti();
opCld: return interpretCld();
opStd: return interpretStd();
opGrp4: return interpretGrp4(instruction);
opGrp5: return interpretGrp5(instruction);

error:
    ERR("invalid opcode used: %d", instruction->opcode);
    return;
}

/*00*/
inline void Interpreter::interpretAddRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 + operand2;
    *rmAddress = LOW(result);

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADD8);
}

/*01*/
inline void Interpreter::interpretAddRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 + operand2;
    *WORD(rmAddress) = result;

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADD16);
}

/*02*/
inline void Interpreter::interpretAddRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 + operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
}

/*03*/
inline void Interpreter::interpretAddRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 + operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD16);
}

/*04*/
inline void Interpreter::interpretAddAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 + operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
}

/*05*/
inline void Interpreter::interpretAddAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

    result = operand1 + operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD16);
}

/*06*/
inline void Interpreter::interpretPushEs() {
    push(machine.cpu.es.data);
}

/*07*/
inline void Interpreter::interpretPopEs() {
    machine.cpu.es.data = pop();
}

/*08*/
inline void Interpreter::interpretOrRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 | operand2;
    *rmAddress = LOW(result);

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::LOG8);
}

/*09*/
inline void Interpreter::interpretOrRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 | operand2;
    *WORD(rmAddress) = result;

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::LOG16);
}

/*0A*/
inline void Interpreter::interpretOrRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 | operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

/*0B*/
inline void Interpreter::interpretOrRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 | operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

/*0C*/
inline void Interpreter::interpretOrAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 | operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

/*0D*/
inline void Interpreter::interpretOrAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

    result = operand1 | operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

/*0E*/
inline void Interpreter::interpretPushCs() {
    push(machine.cpu.cs.data);
}

/*0F*/
inline void Interpreter::interpretPopCs() {
    machine.cpu.cs.data = pop();
}

/*10*/
inline void Interpreter::interpretAdcRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *rmAddress = LOW(result);

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADC8);
}

/*11*/
inline void Interpreter::interpretAdcRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *WORD(rmAddress) = result;

    machine.cpu.flagsRegister.set(operand2, operand1, result, FlagsRegister::ADC16);
}

/*12*/
inline void Interpreter::interpretAdcRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
}

/*13*/
inline void Interpreter::interpretAdcRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC16);
}

/*14*/
inline void Interpreter::interpretAdcAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
}

/*15*/
inline void Interpreter::interpretAdcAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC16);
}

/*16*/
inline void Interpreter::interpretPushSs() {
    push(machine.cpu.ss.data);
}

/*17*/
inline void Interpreter::interpretPopSs() {
    machine.cpu.ss.data = pop();
}

/*18*/
inline void Interpreter::interpretSbbRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *rmAddress;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *rmAddress = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
}

/*19*/
inline void Interpreter::interpretSbbRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *WORD(rmAddress);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *WORD(rmAddress) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB16);
}

/*1A*/
inline void Interpreter::interpretSbbRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
}

/*1B*/
inline void Interpreter::interpretSbbRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB16);
}

/*1C*/
inline void Interpreter::interpretSbbAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
}

/*1D*/
inline void Interpreter::interpretSbbAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB16);
}

/*1E*/
inline void Interpreter::interpretPushDs() {
    push(machine.cpu.ds.data);
}

/*1F*/
inline void Interpreter::interpretPopDs() {
    machine.cpu.ds.data = pop();
}

/*20*/
inline void Interpreter::interpretAndRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *rmAddress;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 & operand2;
    *rmAddress = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

/*21*/
inline void Interpreter::interpretAndRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *WORD(rmAddress);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 & operand2;
    *WORD(rmAddress) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

/*22*/
inline void Interpreter::interpretAndRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 & operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

/*23*/
inline void Interpreter::interpretAndRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 & operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

/*24*/
inline void Interpreter::interpretAndAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 & operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

/*25*/
inline void Interpreter::interpretAndAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

    result = operand1 & operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

/*27*/
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

/*28*/
inline void Interpreter::interpretSubRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *rmAddress;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 - operand2;
    *rmAddress = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

/*29*/
inline void Interpreter::interpretSubRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *WORD(rmAddress);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 - operand2;
    *WORD(rmAddress) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

/*2A*/
inline void Interpreter::interpretSubRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 - operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

/*2B*/
inline void Interpreter::interpretSubRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 - operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

/*2C*/
inline void Interpreter::interpretSubAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 - operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

/*2D*/
inline void Interpreter::interpretSubAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

    result = operand1 - operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

/*2F*/
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

/*30*/
inline void Interpreter::interpretXorRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *rmAddress;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 ^ operand2;
    *rmAddress = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

/*31*/
inline void Interpreter::interpretXorRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *WORD(rmAddress);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 ^ operand2;
    *WORD(rmAddress) = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

/*32*/
inline void Interpreter::interpretXorRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 ^ operand2;
    *machine.cpu.registerAddressTable[instruction->reg] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

/*33*/
inline void Interpreter::interpretXorRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 ^ operand2;
    machine.cpu.registerTable[instruction->reg]->data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

/*34*/
inline void Interpreter::interpretXorAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 ^ operand2;
    *machine.cpu.registerAddressTable[Cpu::AL] = LOW(result);

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

/*35*/
inline void Interpreter::interpretXorAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

    result = operand1 ^ operand2;
    machine.cpu.ax.data = result;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

/*37*/
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

/*38*/
inline void Interpreter::interpretCmpRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *rmAddress;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

/*39*/
inline void Interpreter::interpretCmpRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *WORD(rmAddress);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

/*3A*/
inline void Interpreter::interpretCmpRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *machine.cpu.registerAddressTable[instruction->reg];
    operand2 = *rmAddress;

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

/*3B*/
inline void Interpreter::interpretCmpRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = machine.cpu.registerTable[instruction->reg]->data;
    operand2 = *WORD(rmAddress);

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

/*3C*/
inline void Interpreter::interpretCmpAlIb(Instruction *instruction) {
    operand1 = *machine.cpu.registerAddressTable[Cpu::AL];
    operand2 = instruction->immediate;

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

/*3D*/
inline void Interpreter::interpretCmpAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;

    result = operand1 - operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);
}

/*3F*/
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

/*40*/
inline void Interpreter::interpretIncEax() {
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.ax.data, FlagsRegister::INC16);
}

/*41*/
inline void Interpreter::interpretIncEcx() {
    operand1 = machine.cpu.cx.data;
    machine.cpu.cx.data = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.cx.data, FlagsRegister::INC16);
}

/*42*/
inline void Interpreter::interpretIncEdx() {
    operand1 = machine.cpu.dx.data;
    machine.cpu.dx.data = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.dx.data, FlagsRegister::INC16);
}

/*43*/
inline void Interpreter::interpretIncEbx() {
    operand1 = machine.cpu.bx.data;
    machine.cpu.bx.data = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.bx.data, FlagsRegister::INC16);
}

/*44*/
inline void Interpreter::interpretIncEsp() {
    operand1 = machine.cpu.sp.data;
    machine.cpu.sp.data = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.sp.data, FlagsRegister::INC16);
}

/*45*/
inline void Interpreter::interpretIncEbp() {
    operand1 = machine.cpu.bp.data;
    machine.cpu.bp.data = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.bp.data, FlagsRegister::INC16);
}

/*46*/
inline void Interpreter::interpretIncEsi() {
    operand1 = machine.cpu.si.data;
    machine.cpu.si.data = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.si.data, FlagsRegister::INC16);
}

/*47*/
inline void Interpreter::interpretIncEdi() {
    operand1 = machine.cpu.di.data;
    machine.cpu.di.data = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.di.data, FlagsRegister::INC16);
}

/*48*/
inline void Interpreter::interpretDecEax() {
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.ax.data, FlagsRegister::DEC16);
}

/*49*/
inline void Interpreter::interpretDecEcx() {
    operand1 = machine.cpu.cx.data;
    machine.cpu.cx.data = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.cx.data, FlagsRegister::DEC16);
}

/*4A*/
inline void Interpreter::interpretDecEdx() {
    operand1 = machine.cpu.dx.data;
    machine.cpu.dx.data = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.dx.data, FlagsRegister::DEC16);
}

/*4B*/
inline void Interpreter::interpretDecEbx() {
    operand1 = machine.cpu.bx.data;
    machine.cpu.bx.data = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.bx.data, FlagsRegister::DEC16);
}

/*4C*/
inline void Interpreter::interpretDecEsp() {
    operand1 = machine.cpu.sp.data;
    machine.cpu.sp.data = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.sp.data, FlagsRegister::DEC16);
}

/*4D*/
inline void Interpreter::interpretDecEbp() {
    operand1 = machine.cpu.bp.data;
    machine.cpu.bp.data = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.bp.data, FlagsRegister::DEC16);
}

/*4E*/
inline void Interpreter::interpretDecEsi() {
    operand1 = machine.cpu.si.data;
    machine.cpu.si.data = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.si.data, FlagsRegister::DEC16);
}

/*4F*/
inline void Interpreter::interpretDecEdi() {
    operand1 = machine.cpu.di.data;
    machine.cpu.di.data = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), machine.cpu.di.data, FlagsRegister::DEC16);
}

/*50*/
inline void Interpreter::interpretPushEax() {
    push(machine.cpu.ax.data);
}

/*51*/
inline void Interpreter::interpretPushEcx() {
    push(machine.cpu.cx.data);
}

/*52*/
inline void Interpreter::interpretPushEdx() {
    push(machine.cpu.dx.data);
}

/*53*/
inline void Interpreter::interpretPushEbx() {
    push(machine.cpu.bx.data);
}

/*54*/
inline void Interpreter::interpretPushEsp() {
    push(machine.cpu.sp.data);
}

/*55*/
inline void Interpreter::interpretPushEbp() {
    push(machine.cpu.bp.data);
}

/*56*/
inline void Interpreter::interpretPushEsi() {
    push(machine.cpu.si.data);
}

/*57*/
inline void Interpreter::interpretPushEdi() {
    push(machine.cpu.di.data);
}

/*58*/
inline void Interpreter::interpretPopEax() {
    machine.cpu.ax.data = pop();
}

/*59*/
inline void Interpreter::interpretPopEcx() {
    machine.cpu.cx.data = pop();
}

/*5A*/
inline void Interpreter::interpretPopEdx() {
    machine.cpu.dx.data = pop();
}

/*5B*/
inline void Interpreter::interpretPopEbx() {
    machine.cpu.bx.data = pop();
}

/*5C*/
inline void Interpreter::interpretPopEsp() {
    machine.cpu.sp.data = pop();
}

/*5D*/
inline void Interpreter::interpretPopEbp() {
    machine.cpu.bp.data = pop();
}

/*5E*/
inline void Interpreter::interpretPopEsi() {
    machine.cpu.si.data = pop();
}

/*5F*/
inline void Interpreter::interpretPopEdi() {
    machine.cpu.di.data = pop();
}

/*60*/
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

/*61*/
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

/*62*/
inline void Interpreter::interpretBound(Instruction *instruction) {
    static uint16_t index, lowerBound, upperBound;

    decodeAddress16(instruction);

    index = machine.cpu.registerTable[instruction->reg]->data;
    lowerBound = *WORD(rmAddress);
    upperBound = *(WORD(rmAddress) + 1);

    if(index < lowerBound || index > (upperBound + 2)) {
        machine.cpu.interruptHandler->call(5);
    }
}

/*68*/
inline void Interpreter::interpretImulIw(Instruction *instruction) {
    static int32_t tempResult;

    decodeAddress16(instruction);

    operand1 = *WORD(rmAddress);
    operand2 = instruction->immediate;

    tempResult = operand1 * operand2;

    machine.cpu.registerTable[instruction->reg]->data = tempResult;

    machine.cpu.flagsRegister.set(tempResult >> 16, FlagsRegister::IMUL16);
}

/*69*/
inline void Interpreter::interpretPushIw(Instruction *instruction) {
    push(instruction->immediate);
}

/*6A*/
inline void Interpreter::interpretImulIb(Instruction *instruction) {
    static int32_t tempResult;

    decodeAddress8(instruction);

    operand1 = *WORD(rmAddress);
    operand2 = instruction->immediate;

    tempResult = operand1 * operand2;

    machine.cpu.registerTable[instruction->reg]->data = tempResult;

    machine.cpu.flagsRegister.set(tempResult >> 16, FlagsRegister::IMUL8);
}

/*6B*/
inline void Interpreter::interpretPushIb(Instruction *instruction) {
    push(instruction->immediate);
}

/*6C*/
inline void Interpreter::interpretInsb(Instruction* instruction) {
    LOW(machine.cpu.ax.data) = machine.portHandler.in8(machine.cpu.dx.data);

    processLoop(instruction, 1);
}

/*6D*/
inline void Interpreter::interpretInsw(Instruction* instruction) {
    machine.cpu.ax.data = machine.portHandler.in16(machine.cpu.dx.data);

    processLoop(instruction, 2);
}

/*6E*/
inline void Interpreter::interpretOutsb(Instruction* instruction) {
    machine.portHandler.out8(machine.cpu.dx.data, LOW(machine.cpu.ax.data));

    processLoop(instruction, 1);
}

/*6F*/
inline void Interpreter::interpretOutsw(Instruction* instruction) {
    machine.portHandler.out16(machine.cpu.dx.data, machine.cpu.ax.data);

    processLoop(instruction, 2);
}

/*70*/
inline void Interpreter::interpretJo(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*71*/
inline void Interpreter::interpretJno(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*72*/
inline void Interpreter::interpretJb(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getCf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*73*/
inline void Interpreter::interpretJnb(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getCf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*74*/
inline void Interpreter::interpretJz(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*75*/
inline void Interpreter::interpretJnz(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*76*/
inline void Interpreter::interpretJbe(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getCf() || machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*77*/
inline void Interpreter::interpretJa(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getCf() && !machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*78*/
inline void Interpreter::interpretJs(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getSf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*79*/
inline void Interpreter::interpretJns(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getSf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*7A*/
inline void Interpreter::interpretJpe(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getPf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*7B*/
inline void Interpreter::interpretJpo(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getPf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*7C*/
inline void Interpreter::interpretJl(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getSf() != machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*7D*/
inline void Interpreter::interpretJge(Instruction *instruction) {
    if(machine.cpu.flagsRegister.getSf() == machine.cpu.flagsRegister.getOf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*7E*/
inline void Interpreter::interpretJle(Instruction *instruction) {
    if((machine.cpu.flagsRegister.getSf() != machine.cpu.flagsRegister.getOf()) || machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*7F*/
inline void Interpreter::interpretJg(Instruction *instruction) {
    if(!machine.cpu.flagsRegister.getZf() && (machine.cpu.flagsRegister.getOf() == machine.cpu.flagsRegister.getSf())) {
        machine.cpu.ip.data += (int8_t)instruction->immediate;
    }
}

/*80*/ /*82*/
inline void Interpreter::interpretGrpRmbIb(Instruction *instruction) {
    static const void* jumpTable[] = {
        &&opAdd, &&opOr, &&opAdc, &&opSbb, &&opAnd8, &&opSub8, &&opXor8, &&opFlagSub
    };

    decodeAddress8(instruction);

    operand1 = *rmAddress;
    operand2 = instruction->immediate;

    goto *jumpTable[instruction->reg];

opAdd:
    result = operand1 + operand2;
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
opOr:
    result = operand1 | operand2;
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opAdc:
    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
opSbb:
    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
opAnd8:
    result = operand1 & operand2;
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opSub8:
    result = operand1 - operand2;
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
opXor8:
    result = operand1 ^ operand2;
    *rmAddress = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opFlagSub:
    result = operand1 - operand2;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

/*81*/
inline void Interpreter::interpretGrpRmwIw(Instruction *instruction) {
    static const void* jumpTable[] = {
        &&opAdd, &&opOr, &&opAdc, &&opSbb, &&opAnd8, &&opSub8, &&opXor8, &&opFlagSub
    };

    decodeAddress8(instruction);

    operand1 = *WORD(rmAddress);
    operand2 = instruction->immediate;

    goto *jumpTable[instruction->reg];

opAdd:
    result = operand1 + operand2;
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
opOr:
    result = operand1 | operand2;
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opAdc:
    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
opSbb:
    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
opAnd8:
    result = operand1 & operand2;
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opSub8:
    result = operand1 - operand2;
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
opXor8:
    result = operand1 ^ operand2;
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opFlagSub:
    result = operand1 - operand2;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

/*83*/
inline void Interpreter::interpretGrpRmwIb(Instruction *instruction) {
    static const void* jumpTable[] = {
        &&opAdd, &&opOr, &&opAdc, &&opSbb, &&opAnd8, &&opSub8, &&opXor8, &&opFlagSub
    };

    decodeAddress8(instruction);

    operand1 = *WORD(rmAddress);
    operand2 = instruction->immediate;

    goto *jumpTable[instruction->reg];

opAdd:
    result = operand1 + operand2;
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADD8);
opOr:
    result = operand1 | operand2;
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opAdc:
    result = operand1 + operand2 + machine.cpu.flagsRegister.getCf();
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::ADC8);
opSbb:
    result = operand1 - (operand2 + machine.cpu.flagsRegister.getCf());
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SBB8);
opAnd8:
    result = operand1 & operand2;
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opSub8:
    result = operand1 - operand2;
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
opXor8:
    result = operand1 ^ operand2;
    *WORD(rmAddress) = result;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
opFlagSub:
    result = operand1 - operand2;
    return machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);
}

/*84*/
inline void Interpreter::interpretTestRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *rmAddress;
    operand2 = *machine.cpu.registerAddressTable[instruction->reg];

    result = operand1 & operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

/*85*/
inline void Interpreter::interpretTestRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *WORD(rmAddress);
    operand2 = machine.cpu.registerTable[instruction->reg]->data;

    result = operand1 & operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

/*86*/
inline void Interpreter::interpretXchgRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    operand1 = *rmAddress;
    *rmAddress = *machine.cpu.registerAddressTable[instruction->reg];
    *machine.cpu.registerAddressTable[instruction->reg] = operand1;
}

/*87*/
inline void Interpreter::interpretXchgRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    operand1 = *WORD(rmAddress);
    *WORD(rmAddress) = machine.cpu.registerTable[instruction->reg]->data;
    machine.cpu.registerTable[instruction->reg]->data = operand1;
}

/*88*/
inline void Interpreter::interpretMovRmbRb(Instruction *instruction) {
    decodeAddress8(instruction);

    *rmAddress = *machine.cpu.registerAddressTable[instruction->reg];
}

/*89*/
inline void Interpreter::interpretMovRmwRw(Instruction *instruction) {
    decodeAddress16(instruction);

    *WORD(rmAddress) = machine.cpu.registerTable[instruction->reg]->data;
}

/*8A*/
inline void Interpreter::interpretMovRbRmb(Instruction *instruction) {
    decodeAddress8(instruction);

    *machine.cpu.registerAddressTable[instruction->reg] = *rmAddress;
}

/*8B*/
inline void Interpreter::interpretMovRwRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    machine.cpu.registerTable[instruction->reg]->data = *WORD(rmAddress);
}

/*8C*/
inline void Interpreter::interpretMovRmwSr(Instruction *instruction) {
    decodeAddress16(instruction);

    *WORD(rmAddress) = machine.cpu.segmentRegisterTable[instruction->reg]->data;
}

/*8D*/
inline void Interpreter::interpretLea(Instruction *instruction) {
    decodeAddress16(instruction);

    machine.cpu.registerTable[instruction->reg]->data = decodeRelativeAddress(instruction);
}

/*8E*/
inline void Interpreter::interpretMovSrRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    machine.cpu.segmentRegisterTable[instruction->reg]->data = *WORD(rmAddress);
}

/*8F*/
inline void Interpreter::interpretPopRmw(Instruction *instruction) {
    decodeAddress16(instruction);

    *WORD(rmAddress) = pop();
}

/*91*/
inline void Interpreter::interpretXchgEcxEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.cx.data;
    machine.cpu.cx.data = operand1;
}

/*92*/
inline void Interpreter::interpretXchgEdxEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.dx.data;
    machine.cpu.dx.data = operand1;
}

/*93*/
inline void Interpreter::interpretXchgEbxEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.bx.data;
    machine.cpu.bx.data = operand1;
}

/*94*/
inline void Interpreter::interpretXchgEspEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.sp.data;
    machine.cpu.sp.data = operand1;
}

/*95*/
inline void Interpreter::interpretXchgEbpEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.bp.data;
    machine.cpu.bp.data = operand1;
}

/*96*/
inline void Interpreter::interpretXchgEsiEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.si.data;
    machine.cpu.si.data = operand1;
}

/*97*/
inline void Interpreter::interpretXchgEdiEax(){
    operand1 = machine.cpu.ax.data;
    machine.cpu.ax.data = machine.cpu.di.data;
    machine.cpu.di.data = operand1;
}

/*98*/
inline void Interpreter::interpretCbw(){
    *machine.cpu.registerAddressTable[machine.cpu.AH] = 0 - ((*machine.cpu.registerAddressTable[machine.cpu.AL]) >> 7);
}

/*99*/
inline void Interpreter::interpretCwd(){
    machine.cpu.dx.data = 0 - ((*machine.cpu.registerAddressTable[machine.cpu.AH]) >> 7);
}

/*9A*/
inline void Interpreter::interpretCall(Instruction *instruction){
    push(machine.cpu.cs.data);
    push(machine.cpu.ip.data);

    /*instruction length is always added after interpreter return*/
    machine.cpu.ip.data = instruction->immediate;
    machine.cpu.cs.data = instruction->displacement;
}

/*9B*/
inline void Interpreter::interpretWait(){
    //señor nada
}

/*9C*/
inline void Interpreter::interpretPushF(){
    push(machine.cpu.flagsRegister.toWord());
}

/*9D*/
inline void Interpreter::interpretPopF(){
    machine.cpu.flagsRegister.fromWord(pop());
}

/*9E*/
inline void Interpreter::interpretSahF(){
    machine.cpu.flagsRegister.fromByte(*machine.cpu.registerAddressTable[machine.cpu.AH]);
}

/*9F*/
inline void Interpreter::interpretLahF(){
    *machine.cpu.registerAddressTable[machine.cpu.AH] = machine.cpu.flagsRegister.toByte();
}

/*A0*/
inline void Interpreter::interpretMovAlRmb(Instruction *instruction) {
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + instruction->immediate;
    LOW(machine.cpu.ax.data) = machine.ram.buffer[operand1];
}

/*A1*/
inline void Interpreter::interpretMovAxRmw(Instruction *instruction) {
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + instruction->immediate;
    machine.cpu.ax.data = *WORD(&machine.ram.buffer[operand1]);
}

/*A2*/
inline void Interpreter::interpretMovRmbAl(Instruction *instruction) {
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + instruction->immediate;
    machine.ram.buffer[operand1] = LOW(machine.cpu.ax.data);
}

/*A3*/
inline void Interpreter::interpretMovRmwAx(Instruction *instruction) {
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + instruction->immediate;
    *WORD(&machine.ram.buffer[operand1]) = machine.cpu.ax.data;
}

/*A4*/
inline void Interpreter::interpretMovsb(Instruction *instruction) {
    /*source address*/
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + machine.cpu.si.data;
    /*destination address*/
    operand2 = (machine.cpu.es.data << 4) + machine.cpu.di.data;

    machine.ram.buffer[operand2] = machine.ram.buffer[operand1];

    processLoop(instruction, 1);
}

/*A5*/
inline void Interpreter::interpretMovsw(Instruction *instruction) {
    /*source address*/
    operand1 = (decodeBaseRegisterValue(instruction) << 4) + machine.cpu.si.data;
    /*destination address*/
    operand2 = (machine.cpu.es.data << 4) + machine.cpu.di.data;

    machine.ram.buffer[operand2] = machine.ram.buffer[operand1];
    machine.ram.buffer[operand2 + 1] = machine.ram.buffer[operand1 + 1];

    processLoop(instruction, 2);
}

/*A6*/
inline void Interpreter::interpretCmpsb(Instruction *instruction) {
    /*source value*/
    operand1 = machine.ram.buffer[(decodeBaseRegisterValue(instruction) << 4) + machine.cpu.si.data];
    /*destination value*/
    operand2 = machine.ram.buffer[(machine.cpu.es.data << 4) + machine.cpu.di.data];

    result = operand1 - operand2;
    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB8);

    processLoop(instruction, 1);
}

/*A7*/
inline void Interpreter::interpretCmpsw(Instruction *instruction) {
    /*source value*/
    operand1 = *WORD(&machine.ram.buffer[(decodeBaseRegisterValue(instruction) << 4) + machine.cpu.si.data]);
    /*destination value*/
    operand2 = *WORD(&machine.ram.buffer[(machine.cpu.es.data << 4) + machine.cpu.di.data]);

    result = operand1 - operand2;
    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::SUB16);

    processLoop(instruction, 2);
}

/*A8*/
inline void Interpreter::interpretTestAlIb(Instruction *instruction) {
    operand1 = LOW(machine.cpu.ax.data);
    operand2 = instruction->immediate;
    result = operand1 & operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG8);
}

/*A9*/
inline void Interpreter::interpretTestAxIw(Instruction *instruction) {
    operand1 = machine.cpu.ax.data;
    operand2 = instruction->immediate;
    result = operand1 & operand2;

    machine.cpu.flagsRegister.set(operand1, operand2, result, FlagsRegister::LOG16);
}

/*AA*/
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

/*AB*/
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

/*AC*/
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

/*AD*/
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

/*AE*/
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

/*AF*/
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

/*B0*/
inline void Interpreter::interpretMovAlIb(Instruction* instruction){
    LOW(machine.cpu.ax.data) = instruction->immediate;
}

/*B1*/
inline void Interpreter::interpretMovClIb(Instruction* instruction){
    LOW(machine.cpu.cx.data) = instruction->immediate;
}

/*B2*/
inline void Interpreter::interpretMovDlIb(Instruction* instruction){
    LOW(machine.cpu.dx.data) = instruction->immediate;
}

/*B3*/
inline void Interpreter::interpretMovBlIb(Instruction* instruction){
    LOW(machine.cpu.bx.data) = instruction->immediate;
}

/*B4*/
inline void Interpreter::interpretMovAhIb(Instruction* instruction){
    HIGH(machine.cpu.ax.data) = instruction->immediate;
}

/*B5*/
inline void Interpreter::interpretMovChIb(Instruction* instruction){
    HIGH(machine.cpu.cx.data) = instruction->immediate;
}

/*B6*/
inline void Interpreter::interpretMovDhIb(Instruction* instruction){
    HIGH(machine.cpu.dx.data) = instruction->immediate;
}

/*B7*/
inline void Interpreter::interpretMovBhIb(Instruction* instruction){
    HIGH(machine.cpu.bx.data) = instruction->immediate;
}

/*B8*/
inline void Interpreter::interpretMovEaxIw(Instruction* instruction){
    machine.cpu.ax.data = instruction->immediate;
}

/*B9*/
inline void Interpreter::interpretMovEcxIw(Instruction* instruction){
    machine.cpu.cx.data = instruction->immediate;
}

/*BA*/
inline void Interpreter::interpretMovEdxIw(Instruction* instruction){
    machine.cpu.dx.data = instruction->immediate;
}

/*BB*/
inline void Interpreter::interpretMovEbxIw(Instruction* instruction){
    machine.cpu.bx.data = instruction->immediate;
}

/*BC*/
inline void Interpreter::interpretMovEspIw(Instruction* instruction){
    machine.cpu.sp.data = instruction->immediate;
}

/*BD*/
inline void Interpreter::interpretMovEbpIw(Instruction* instruction){
    machine.cpu.bp.data = instruction->immediate;
}

/*BE*/
inline void Interpreter::interpretMovEsiIw(Instruction* instruction){
    machine.cpu.si.data = instruction->immediate;
}

/*BF*/
inline void Interpreter::interpretMovEdiIw(Instruction* instruction){
    machine.cpu.di.data = instruction->immediate;
}

/*C0*/
inline void Interpreter::interpretGrpRmbIb2(Instruction *instruction) {
    decodeAddress8(instruction);

    /*value*/
    operand1 = *rmAddress;
    /*how many time*/
    operand2 = instruction->immediate & 0x1F;

    /*for 0 shifts or rotates, the flags should be unaffected*/
    if(!operand2) {
        return;
    }

    interpretBitGrp8(instruction);
}

/*C1*/
inline void Interpreter::interpretGrpRmwIb2(Instruction *instruction) {
    decodeAddress16(instruction);

    /*value*/
    operand1 = *WORD(rmAddress);
    /*how many time*/
    operand2 = instruction->immediate & 0x1F;

    /*for 0 shifts or rotates, the flags should be unaffected*/
    if(!operand2) {
        return;
    }

    interpretBitGrp16(instruction);
}

/*C2*/
inline void Interpreter::interpretRetIw(Instruction *instruction) {
    machine.cpu.ip.data = pop();
    machine.cpu.sp.data += instruction->immediate;
}

/*C3*/
inline void Interpreter::interpretRet() {
    machine.cpu.ip.data = pop();
}

/*C4*/
inline void Interpreter::interpretLes(Instruction *instruction) {
    decodeAddress16(instruction);
    machine.cpu.registerTable[instruction->reg]->data = *WORD(rmAddress);
    machine.cpu.es.data = *WORD(rmAddress + 2);
}

/*C5*/
inline void Interpreter::interpretLds(Instruction *instruction) {
    decodeAddress16(instruction);
    machine.cpu.registerTable[instruction->reg]->data = *WORD(rmAddress);
    machine.cpu.ds.data = *WORD(rmAddress + 2);
}

/*C6*/
inline void Interpreter::interpretMovRmbIb(Instruction* instruction){
    decodeAddress8(instruction);
    *rmAddress = instruction->immediate;
}

/*C7*/
inline void Interpreter::interpretMovRmwIw(Instruction* instruction){
    decodeAddress16(instruction);
    *WORD(rmAddress) = instruction->immediate;
}

/*C8*/
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

/*C9*/
inline void Interpreter::interpretLeave() {
    machine.cpu.sp.data = machine.cpu.bp.data;
    machine.cpu.bp.data = pop();
}

/*CA*/
inline void Interpreter::interpretRetfIw(Instruction* instruction) {
    machine.cpu.ip.data = pop();
    machine.cpu.cs.data = pop();
    machine.cpu.sp.data += instruction->immediate;
}

/*CB*/
inline void Interpreter::interpretRetf() {
    machine.cpu.ip.data = pop();
    machine.cpu.cs.data = pop();
}

/*CC*/
inline void Interpreter::interpretInt3() {
    machine.cpu.interruptHandler->call(3);
}

/*CD*/
inline void Interpreter::interpretIntIb(Instruction* instruction) {
    machine.cpu.interruptHandler->call(instruction->immediate);
}

/*CE*/
inline void Interpreter::interpretInto() {
    if(machine.cpu.flagsRegister.getOf()) {
        machine.cpu.interruptHandler->call(4);
    }
}

/*CF*/
inline void Interpreter::interpretIret() {
    machine.cpu.ip.data = pop();
    machine.cpu.cs.data = pop();

    /*flags*/
    interpretPopF();
}

/*D0*/
inline void Interpreter::interpretGrpRmb1(Instruction *instruction) {
    decodeAddress8(instruction);

    /*value*/
    operand1 = *rmAddress;
    /*how many time*/
    operand2 = 1;

    interpretBitGrp8(instruction);
}

/*D1*/
inline void Interpreter::interpretGrpRmw1(Instruction *instruction) {
    decodeAddress16(instruction);

    /*value*/
    operand1 = *WORD(rmAddress);
    /*how many time*/
    operand2 = 1;

    interpretBitGrp16(instruction);
}

/*D2*/
inline void Interpreter::interpretGrpRmbCl(Instruction *instruction) {
    decodeAddress8(instruction);

    /*value*/
    operand1 = *rmAddress;
    /*how many time*/
    operand2 = LOW(machine.cpu.cx.data);

    /*for 0 shifts or rotates, the flags should be unaffected*/
    if(!operand2) {
        return;
    }

    interpretBitGrp8(instruction);
}

/*D3*/
inline void Interpreter::interpretGrpRmwCl(Instruction *instruction) {
    decodeAddress16(instruction);

    /*value*/
    operand1 = *WORD(rmAddress);
    /*how many time*/
    operand2 = LOW(machine.cpu.cx.data);

    /*for 0 shifts or rotates, the flags should be unaffected*/
    if(!operand2) {
        return;
    }

    interpretBitGrp16(instruction);
}

/*D4*/
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

/*D5*/
inline void Interpreter::interpretAad(Instruction *instruction) {
    machine.cpu.ax.data = (HIGH(machine.cpu.ax.data) * instruction->immediate + LOW(machine.cpu.ax.data)) & 0xFF;
    /*instruction doesn't matter as only ZF, PF, SF are set*/
    machine.cpu.flagsRegister.set(machine.cpu.ax.data, FlagsRegister::IMUL16);
}

/*D6*/
inline void Interpreter::interpretXlat() {
    /*I found this in the Fake86 implementation, but no mention in the intel manual*/
    if(machine.cpu.flagsRegister.getCf()) {
        LOW(machine.cpu.ax.data) = 0xFF;
    } else {
        LOW(machine.cpu.ax.data) = 0x00;
    }
}

/*D7*/
inline void Interpreter::interpretXlat2(Instruction *instruction) {
    LOW(machine.cpu.ax.data) = (decodeBaseRegisterValue(instruction) << 4)
            + machine.cpu.bx.data + LOW(machine.cpu.ax.data);

}

/*E0*/
inline void Interpreter::interpretLoopnz(Instruction *instruction) {
    machine.cpu.cx.data -= 1;

    if(machine.cpu.cx.data && !machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += SIGNED8(instruction->immediate);
    }
}

/*E1*/
inline void Interpreter::interpretLoopz(Instruction *instruction) {
    machine.cpu.cx.data -= 1;

    if(machine.cpu.cx.data && machine.cpu.flagsRegister.getZf()) {
        machine.cpu.ip.data += SIGNED8(instruction->immediate);
    }
}

/*E2*/
inline void Interpreter::interpretLoop(Instruction *instruction) {
    machine.cpu.cx.data -= 1;

    if(machine.cpu.cx.data) {
        machine.cpu.ip.data += SIGNED8(instruction->immediate);
    }
}

/*E3*/
inline void Interpreter::interpretJcxz(Instruction *instruction) {
    if(!machine.cpu.cx.data) {
        machine.cpu.ip.data += SIGNED8(instruction->immediate);
    }
}

/*E4*/
inline void Interpreter::interpretInAlIb(Instruction *instruction) {
    LOW(machine.cpu.ax.data) = machine.portHandler.in8(instruction->immediate);
}

/*E5*/
inline void Interpreter::interpretInEaxIb(Instruction *instruction) {
    machine.cpu.ax.data = machine.portHandler.in16(instruction->immediate);
}

/*E6*/
inline void Interpreter::interpretOutIbAl(Instruction *instruction) {
    machine.portHandler.out8(instruction->immediate, LOW(machine.cpu.ax.data));
}

/*E7*/
inline void Interpreter::interpretOutIbEax(Instruction *instruction) {
    machine.portHandler.out16(instruction->immediate, machine.cpu.ax.data);
}

/*E8*/
inline void Interpreter::interpretCallIw(Instruction *instruction) {
    push(machine.cpu.ip.data);
    machine.cpu.ip.data += instruction->immediate;
}

/*E9*/
inline void Interpreter::interpretJmp(Instruction *instruction) {
    machine.cpu.ip.data += instruction->immediate;
}

/*EA*/
inline void Interpreter::interpretJmpFar(Instruction *instruction) {
    machine.cpu.ip.data = instruction->immediate;
    machine.cpu.cs.data = instruction->displacement;
}

/*EB*/
inline void Interpreter::interpretJmpShort(Instruction *instruction) {
    machine.cpu.ip.data += SIGNED16(instruction->immediate);
}

/*EC*/
inline void Interpreter::interpretInAlEdx() {
    LOW(machine.cpu.ax.data) = machine.portHandler.in8(machine.cpu.dx.data);
}

/*ED*/
inline void Interpreter::interpretInEaxEdx() {
    machine.cpu.ax.data = machine.portHandler.in16(machine.cpu.dx.data);
}

/*EE*/
inline void Interpreter::interpretOutEdxAl() {
    machine.portHandler.out8(machine.cpu.dx.data, LOW(machine.cpu.ax.data));
}

/*EF*/
inline void Interpreter::interpretOutEdxEax() {
    machine.portHandler.out16(machine.cpu.dx.data, machine.cpu.ax.data);
}

/*F0*/
inline void Interpreter::interpretLock() {
    //todo
}

/*F4*/
inline void Interpreter::interpretHlt() {
    //todo
}

/*F5*/
inline void Interpreter::interpretCmc() {
    machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf() | (machine.cpu.flagsRegister.getOf() << 1), !machine.cpu.flagsRegister.getCf(),
                                  machine.cpu.flagsRegister.result, FlagsRegister::CMC | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
}

/*F6*/
inline void Interpreter::interpretGrpIb3(Instruction* instruction) {
    static void* jumpTable[] {
        &&opTest, &&opTest, &&opNot, &&opNeg, &&opMul, &&opIMul, &&opDiv, &&opIDiv,
    };
    static int32_t tmp;

    decodeAddress8(instruction);
    operand1 = *rmAddress;

    goto *jumpTable[instruction->reg];

opTest:
    machine.cpu.flagsRegister.set(operand1 & instruction->immediate, machine.cpu.flagsRegister.LOG8);
    return;
opNot:
    *rmAddress = ~operand1;
    return;
opNeg:
    *rmAddress = (~operand1) + 1;
    machine.cpu.flagsRegister.set(0, operand1, *rmAddress, machine.cpu.flagsRegister.NEG8);
    return;
opMul:
    machine.cpu.ax.data = LOW(machine.cpu.ax.data) * operand1;
    machine.cpu.flagsRegister.set(machine.cpu.ax.data, FlagsRegister::MUL8);
    return;
opIMul:
    machine.cpu.ax.data = SIGNED16(LOW(machine.cpu.ax.data)) * SIGNED16(operand1);
    machine.cpu.flagsRegister.set(machine.cpu.ax.data, FlagsRegister::IMUL8);
    return;
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
    return;
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

/*F7*/
inline void Interpreter::interpretGrpIw3(Instruction* instruction) {
    static void* jumpTable[] {
        &&opTest, &&opTest, &&opNot, &&opNeg, &&opMul, &&opIMul, &&opDiv, &&opIDiv,
    };
    static int32_t tmp;
    static uint32_t utmp;

    decodeAddress16(instruction);
    operand1 = *WORD(rmAddress);

    goto *jumpTable[instruction->reg];

opTest:
    machine.cpu.flagsRegister.set(operand1 & instruction->immediate, machine.cpu.flagsRegister.LOG16);
    return;
opNot:
    *WORD(rmAddress) = ~operand1;
    return;
opNeg:
    *WORD(rmAddress) = (~operand1) + 1;
    machine.cpu.flagsRegister.set(0, operand1, *WORD(rmAddress), machine.cpu.flagsRegister.NEG16);
    return;
opMul:
    utmp = machine.cpu.ax.data * operand1;

    machine.cpu.ax.data = utmp;
    utmp >>= 16;
    machine.cpu.dx.data = utmp;
    machine.cpu.flagsRegister.set(utmp, FlagsRegister::MUL16);
    return;
opIMul:
    tmp = SIGNED16(machine.cpu.ax.data) * SIGNED16(operand1);

    machine.cpu.ax.data = tmp;
    tmp >>= 16;
    machine.cpu.dx.data = tmp;
    machine.cpu.flagsRegister.set(tmp, FlagsRegister::IMUL8);
    return;
opDiv:
    if(operand1 == 0) {
        machine.cpu.interruptHandler->call(0);
    } else {
        utmp = (machine.cpu.dx.data << 16) | machine.cpu.ax.data;
        utmp = utmp / operand1;

        if(utmp > 0xFFFF) {
            machine.cpu.interruptHandler->call(0);
        } else {
            machine.cpu.ax.data = utmp;
            machine.cpu.dx.data = ((machine.cpu.dx.data << 16) | machine.cpu.ax.data) % operand1;
        }
    }
    return;
opIDiv:
    if(operand1 == 0) {
        machine.cpu.interruptHandler->call(0);
    } else {
        tmp = (machine.cpu.dx.data << 16) | machine.cpu.ax.data;
        tmp = SIGNED16(tmp) / SIGNED16(operand1);

        if(tmp > 0x7FFF || tmp < 0x8000) {
            machine.cpu.interruptHandler->call(0);
        } else {
            machine.cpu.ax.data = tmp;
            machine.cpu.dx.data = ((machine.cpu.dx.data << 16) | machine.cpu.ax.data) % operand1;
        }
    }
}

/*F8*/
inline void Interpreter::interpretClc() {
    machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), machine.cpu.flagsRegister.getOf(), machine.cpu.flagsRegister.result,
                                  FlagsRegister::CMC | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
}

/*F9*/
inline void Interpreter::interpretStc() {
    machine.cpu.flagsRegister.set(machine.cpu.flagsRegister.getAf(), machine.cpu.flagsRegister.getOf(), machine.cpu.flagsRegister.result,
                                  FlagsRegister::CMC | (machine.cpu.flagsRegister.instruction & FlagsRegister::SIZE_MASK));
}

/*FA*/
inline void Interpreter::interpretCli() {
    machine.cpu.flagsRegister.itf = false;
}

/*FB*/
inline void Interpreter::interpretSti() {
    machine.cpu.flagsRegister.itf = true;
}

/*FC*/
inline void Interpreter::interpretCld() {
    machine.cpu.flagsRegister.df = false;
}

/*FD*/
inline void Interpreter::interpretStd() {
    machine.cpu.flagsRegister.df = true;
}

/*FE*/
inline void Interpreter::interpretGrp4(Instruction *instruction) {
    static void* jumpTable[] = { &&opInc, &&opDec };

    decodeAddress16(instruction);
    goto *jumpTable[instruction->reg];

opInc:
    operand1 = *rmAddress;
    *rmAddress = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), *rmAddress, FlagsRegister::INC8);
    return;
opDec:
    operand1 = *rmAddress;
    *rmAddress = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), *rmAddress, FlagsRegister::DEC8);
}

/*FF*/
inline void Interpreter::interpretGrp5(Instruction *instruction) {
    static void* jumpTable[] = {
        &&opInc, &&opDec, &&opCall, &&opCallFar, &&opJmp, &&opJmpFar, &&opPush
    };

    decodeAddress16(instruction);
    goto *jumpTable[instruction->reg];

opInc:
    operand1 = *WORD(rmAddress);
    *WORD(rmAddress) = operand1 + 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), *WORD(rmAddress), FlagsRegister::INC16);
    return;
opDec:
    operand1 = *WORD(rmAddress);
    *WORD(rmAddress) = operand1 - 1;

    machine.cpu.flagsRegister.set(operand1, machine.cpu.flagsRegister.getCf(), *WORD(rmAddress), FlagsRegister::DEC16);
    return;

opCall:
    push(machine.cpu.ip.data);
    machine.cpu.ip.data = *WORD(rmAddress);
    return;
opCallFar:
    push(machine.cpu.cs.data);
    push(machine.cpu.ip.data);

    machine.cpu.ip.data = *WORD(rmAddress);
    machine.cpu.cs.data = *WORD(rmAddress + 2);
    return;
opJmp:
    machine.cpu.ip.data = *WORD(rmAddress);
    return;
opJmpFar:
    machine.cpu.ip.data = *WORD(rmAddress);
    machine.cpu.cs.data = *WORD(rmAddress + 2);
    return;
opPush:
    push(*(WORD(rmAddress)));
}


#endif // INTERPRETER_H
