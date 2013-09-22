#ifndef DECODER_H
#define DECODER_H

#include "common.h"
#include "mem/ram.h"
#include "instruction.h"

class Decoder {
private:
    uint8_t baseRegisterTable[8];
    uint8_t indexRegisterTable[8];
    bool prefixTable[0xFF];
    uint8_t prefixEqTable[0xFF];

    Ram* ram;

    void decodePrefix(uint32_t& address, Instruction *instructon);
    void decodeInstruction(uint32_t& address, Instruction *instructon);

    void decodeModRm(uint32_t& address, Instruction* instruction);

    void decodeGeneric(Instruction *instruction);
    void decodeGenericModRm(uint32_t& address, Instruction *instruction);
    void decodeGenericImmediate8(uint32_t& address, Instruction *instruction);
    void decodeGenericImmediate16(uint32_t& address, Instruction *instruction);

    void decodeImulIw(uint32_t& address, Instruction *instruction);
    void decodeImulIb(uint32_t& address, Instruction *instruction);
    void decodeGrpRmbIb(uint32_t& address, Instruction *instruction);
    void decodeGrpRmwIw(uint32_t& address, Instruction *instruction);
    void decodeCall(uint32_t& address, Instruction *instruction);
    void decodeEnter(uint32_t& address, Instruction *instruction);
    void decodeGrp3Ib(uint32_t& address, Instruction *instruction);
    void decodeGrp3Iw(uint32_t& address, Instruction *instruction);

public:
    Decoder(Ram* ram);

    void decode(uint32_t address, Instruction* instruction);
};

inline void Decoder::decode(uint32_t address, Instruction *instruction) {
    instruction->length = 0;

    decodePrefix(address, instruction);
    decodeInstruction(address, instruction);
}

inline void Decoder::decodePrefix(uint32_t& address, Instruction *instructon) {
    instructon->prefix = 0;

    while(prefixTable[ram->buffer[address]]) {
        instructon->length++;
        instructon->prefix |= prefixEqTable[ram->buffer[address]];
        address++;
    }
}

inline void Decoder::decodeInstruction(uint32_t& address, Instruction *instruction) {
    static const void * jumpTable[] = {
        /*0x00*/ &&opAddRmbRb, &&opAddRmwRw, &&opAddRbRmb, &&opAddRwRmw, &&opAddAlIb, &&opAddAxIw, &&opPushEs, &&opPopEs,
        /*0x08*/ &&opOrRmbRb, &&opOrRmwRw, &&opOrRbRmb, &&opOrRwRmw, &&opOrAlIb, &&opOrAxIw, &&opPushCs, &&opPopCs,
        /*0x10*/ &&opAdcRmbRb, &&opAdcRmwRw, &&opAdcRbRmb, &&opAdcRwRmw, &&opAdcAlIb, &&opAdcAxIw, &&opPushSs, &&opPopSs,
        /*0x18*/ &&opSbbRmbRb, &&opSbbRmwRw, &&opSbbRbRmb, &&opSbbRwRmw, &&opSbbAlIb, &&opSbbAxIw, &&opPushDs, &&opPopDs,
        /*0x20*/ &&opAndRmbRb, &&opAndRmwRw, &&opAndRbRmb, &&opAndRwRmw, &&opAndAlIb, &&opAndAxIw, &&error, &&opDaa,
        /*0x28*/ &&opSubRmbRb, &&opSubRmwRw, &&opSubRbRmb, &&opSubRwRmw, &&opSubAlIb, &&opSubAxIw, &&error, &&opDas,
        /*0x30*/ &&opXorRmbRb, &&opXorRmwRw, &&opXorRbRmb, &&opXorRwRmw, &&opXorAlIb, &&opXorAxIw, &&error, &&opAaa,
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
        /*0xD8*/ &&opFadd, &&opFcos, &&opFiadd, &&opFist, &&opFsub, &&opFst, &&opFmulp, &&Fnstsw,
        /*0xE0*/ &&opLoopnz, &&opLoopz, &&opLoop, &&opJcxz, &&opInAlIb, &&opEaxIb, &&opOutIbAl, &&opOutIbEax,
        /*0xE8*/ &&opCallIw, &&opJmp, &&opJmpFar, &&opJmpShort, &&opInAlEdx, &&opInEaxEdx, &&opOutEdxAl, &&opOutEdxEax,
        /*0xF0*/ &&opLock, &&error, &&error, &&error, &&opHlt, &&opCmc, &&opGrpIb3, &&opGrpIw3,
        /*0xF8*/ &&opClc, &&opStc, &&opCli, &&opSti, &&opCld, &&opStd, &&opGrp4, &&opGrp5
    };

    instruction->opcode = ram->buffer[address++];
    goto *jumpTable[instruction->opcode];

opAddRmbRb: return decodeGenericModRm(address, instruction);
opAddRmwRw: return decodeGenericModRm(address, instruction);
opAddRbRmb: return decodeGenericModRm(address, instruction);
opAddRwRmw: return decodeGenericModRm(address, instruction);
opAddAlIb: return decodeGenericImmediate8(address, instruction);
opAddAxIw: return decodeGenericImmediate16(address, instruction);

opPushEs: return decodeGeneric(instruction);
opPopEs: return decodeGeneric(instruction);

opOrRmbRb: return decodeGenericModRm(address, instruction);
opOrRmwRw: return decodeGenericModRm(address, instruction);
opOrRbRmb: return decodeGenericModRm(address, instruction);
opOrRwRmw: return decodeGenericModRm(address, instruction);
opOrAlIb: return decodeGenericImmediate8(address, instruction);
opOrAxIw: return decodeGenericImmediate16(address, instruction);

opPushCs: return decodeGeneric(instruction);
opPopCs: return decodeGeneric(instruction);

opAdcRmbRb: return decodeGenericModRm(address, instruction);
opAdcRmwRw: return decodeGenericModRm(address, instruction);
opAdcRbRmb: return decodeGenericModRm(address, instruction);
opAdcRwRmw: return decodeGenericModRm(address, instruction);
opAdcAlIb: return decodeGenericImmediate8(address, instruction);
opAdcAxIw: return decodeGenericImmediate16(address, instruction);

opPushSs: return decodeGeneric(instruction);
opPopSs: return decodeGeneric(instruction);

opSbbRmbRb: return decodeGenericModRm(address, instruction);
opSbbRmwRw: return decodeGenericModRm(address, instruction);
opSbbRbRmb: return decodeGenericModRm(address, instruction);
opSbbRwRmw: return decodeGenericModRm(address, instruction);
opSbbAlIb: return decodeGenericImmediate8(address, instruction);
opSbbAxIw: return decodeGenericImmediate16(address, instruction);

opPushDs: return decodeGeneric(instruction);
opPopDs: return decodeGeneric(instruction);

opAndRmbRb: return decodeGenericModRm(address, instruction);
opAndRmwRw: return decodeGenericModRm(address, instruction);
opAndRbRmb: return decodeGenericModRm(address, instruction);
opAndRwRmw: return decodeGenericModRm(address, instruction);
opAndAlIb: return decodeGenericImmediate8(address, instruction);
opAndAxIw: return decodeGenericImmediate16(address, instruction);

opDaa: return decodeGeneric(instruction);

opSubRmbRb: return decodeGenericModRm(address, instruction);
opSubRmwRw: return decodeGenericModRm(address, instruction);
opSubRbRmb: return decodeGenericModRm(address, instruction);
opSubRwRmw: return decodeGenericModRm(address, instruction);
opSubAlIb: return decodeGenericImmediate8(address, instruction);
opSubAxIw: return decodeGenericImmediate16(address, instruction);

opDas: return decodeGeneric(instruction);

opXorRmbRb: return decodeGenericModRm(address, instruction);
opXorRmwRw: return decodeGenericModRm(address, instruction);
opXorRbRmb: return decodeGenericModRm(address, instruction);
opXorRwRmw: return decodeGenericModRm(address, instruction);
opXorAlIb: return decodeGenericImmediate8(address, instruction);
opXorAxIw: return decodeGenericImmediate16(address, instruction);

opAaa: return decodeGeneric(instruction);

opCmpRmbRb: return decodeGenericModRm(address, instruction);
opCmpRmwRw: return decodeGenericModRm(address, instruction);
opCmpRbRmb: return decodeGenericModRm(address, instruction);
opCmpRwRmw: return decodeGenericModRm(address, instruction);
opCmpAlIb: return decodeGenericImmediate8(address, instruction);
opCmpAxIw: return decodeGenericImmediate16(address, instruction);

opAas: return decodeGeneric(instruction);

opIncEax: return decodeGeneric(instruction);
opIncEcx: return decodeGeneric(instruction);
opIncEdx: return decodeGeneric(instruction);
opIncEbx: return decodeGeneric(instruction);
opIncEsp: return decodeGeneric(instruction);
opIncEbp: return decodeGeneric(instruction);
opIncEsi: return decodeGeneric(instruction);
opIncEdi: return decodeGeneric(instruction);

opDecEax: return decodeGeneric(instruction);
opDecEcx: return decodeGeneric(instruction);
opDecEdx: return decodeGeneric(instruction);
opDecEbx: return decodeGeneric(instruction);
opDecEsp: return decodeGeneric(instruction);
opDecEbp: return decodeGeneric(instruction);
opDecEsi: return decodeGeneric(instruction);
opDecEdi: return decodeGeneric(instruction);

opPushEax: return decodeGeneric(instruction);
opPushEcx: return decodeGeneric(instruction);
opPushEdx: return decodeGeneric(instruction);
opPushEbx: return decodeGeneric(instruction);
opPushEsp: return decodeGeneric(instruction);
opPushEbp: return decodeGeneric(instruction);
opPushEsi: return decodeGeneric(instruction);
opPushEdi: return decodeGeneric(instruction);

opPopEax: return decodeGeneric(instruction);
opPopEcx: return decodeGeneric(instruction);
opPopEdx: return decodeGeneric(instruction);
opPopEbx: return decodeGeneric(instruction);
opPopEsp: return decodeGeneric(instruction);
opPopEbp: return decodeGeneric(instruction);
opPopEsi: return decodeGeneric(instruction);
opPopEdi: return decodeGeneric(instruction);

opPusha: return decodeGeneric(instruction);
opPopa: return decodeGeneric(instruction);
opBound: return decodeGenericModRm(address, instruction);

opPushIw: return decodeGenericImmediate16(address, instruction);
opImulIw: return decodeImulIw(address, instruction);
opPushIb: return decodeGenericImmediate8(address, instruction);
opImulIb: return decodeImulIb(address, instruction);

opInsb: return decodeGeneric(instruction);
opInsw: return decodeGeneric(instruction);
opOutsb: return decodeGeneric(instruction);
opOutsw: return decodeGeneric(instruction);

opJo: return decodeGenericImmediate8(address, instruction);
opJno: return decodeGenericImmediate8(address, instruction);
opJb: return decodeGenericImmediate8(address, instruction);
opJnb: return decodeGenericImmediate8(address, instruction);
opJz: return decodeGenericImmediate8(address, instruction);
opJnz: return decodeGenericImmediate8(address, instruction);
opJbe: return decodeGenericImmediate8(address, instruction);
opJa: return decodeGenericImmediate8(address, instruction);
opJs: return decodeGenericImmediate8(address, instruction);
opJns: return decodeGenericImmediate8(address, instruction);
opJpe: return decodeGenericImmediate8(address, instruction);
opJpo: return decodeGenericImmediate8(address, instruction);
opJl: return decodeGenericImmediate8(address, instruction);
opJge: return decodeGenericImmediate8(address, instruction);
opJle: return decodeGenericImmediate8(address, instruction);
opJg: return decodeGenericImmediate8(address, instruction);

opGrpRmbIb: return decodeGrpRmbIb(address, instruction);
opGrpRmwIw: return decodeGrpRmwIw(address, instruction);
opGrpRmwIb: return decodeGrpRmbIb(address, instruction);
opTestRmbRb: return decodeGenericModRm(address, instruction);
opTestRmwRw: return decodeGenericModRm(address, instruction);
opXchgRmbRb: return decodeGenericModRm(address, instruction);
opXchgRmwRw: return decodeGenericModRm(address, instruction);

opMovRmbRb: return decodeGenericModRm(address, instruction);
opMovRmwRw: return decodeGenericModRm(address, instruction);
opMovRbRmb: return decodeGenericModRm(address, instruction);
opMovRwRmw: return decodeGenericModRm(address, instruction);
opMovRmwSr: return decodeGenericModRm(address, instruction);
opLea: return decodeGenericModRm(address, instruction);
opMovSrRmw: return decodeGenericModRm(address, instruction);
opPopRmw: return decodeGenericModRm(address, instruction);

opNop: return decodeGeneric(instruction);
opXchgEcxEax: return decodeGenericModRm(address, instruction);
opXchgEdxEax: return decodeGenericModRm(address, instruction);
opXchgEbxEax: return decodeGenericModRm(address, instruction);
opXchgEspEax: return decodeGenericModRm(address, instruction);
opXchgEbpEax: return decodeGenericModRm(address, instruction);
opXchgEsiEax: return decodeGenericModRm(address, instruction);
opXchgEdiEax: return decodeGenericModRm(address, instruction);

opCbw: return decodeGeneric(instruction);
opCwd: return decodeGeneric(instruction);
opCall: return decodeCall(address, instruction);
opWait: return decodeGeneric(instruction);
opPushF: return decodeGeneric(instruction);
opPopF: return decodeGeneric(instruction);
opSahF: return decodeGeneric(instruction);
opLahF: return decodeGeneric(instruction);

opMovAlRmb: return decodeGenericImmediate16(address, instruction);
opMovAxRmw: return decodeGenericImmediate16(address, instruction);
opMovRmbAl: return decodeGenericImmediate16(address, instruction);
opMovRmwAx: return decodeGenericImmediate16(address, instruction);
opMovsb: return decodeGeneric(instruction);
opMovsw: return decodeGeneric(instruction);
opCmpsb: return decodeGeneric(instruction);
opCmpsw: return decodeGeneric(instruction);

opTestAlIb: return decodeGenericImmediate8(address, instruction);
opTestAxIw: return decodeGenericImmediate16(address, instruction);
opStosb: return decodeGeneric(instruction);
opStosw: return decodeGeneric(instruction);
opLodsb: return decodeGeneric(instruction);
opLodsw: return decodeGeneric(instruction);
opScasb: return decodeGeneric(instruction);
opScasw: return decodeGeneric(instruction);

opMovAlIb: return decodeGenericImmediate8(address, instruction);
opMovClIb: return decodeGenericImmediate8(address, instruction);
opMovDlIb: return decodeGenericImmediate8(address, instruction);
opMovBlIb: return decodeGenericImmediate8(address, instruction);
opMovAhIb: return decodeGenericImmediate8(address, instruction);
opMovChIb: return decodeGenericImmediate8(address, instruction);
opMovDhIb: return decodeGenericImmediate8(address, instruction);
opMovBhIb: return decodeGenericImmediate8(address, instruction);
opMovEaxIw: return decodeGenericImmediate16(address, instruction);
opMovEcxIw: return decodeGenericImmediate16(address, instruction);
opMovEdxIw: return decodeGenericImmediate16(address, instruction);
opMovEbxIw: return decodeGenericImmediate16(address, instruction);
opMovEspIw: return decodeGenericImmediate16(address, instruction);
opMovEbpIw: return decodeGenericImmediate16(address, instruction);
opMovEsiIw: return decodeGenericImmediate16(address, instruction);
opMovEdiIw: return decodeGenericImmediate16(address, instruction);

opGrpRmbIb2: return decodeGrpRmbIb(address, instruction);
opGrpRmwIb2: return decodeGrpRmbIb(address, instruction);
opRetIw: return decodeGenericImmediate16(address, instruction);
opRet: return decodeGeneric(instruction);
opLes: return decodeGenericModRm(address, instruction);
opLds: return decodeGenericModRm(address, instruction);
opMovRmbIb: return decodeGrpRmbIb(address, instruction);
opMovRmwIw: return decodeGrpRmwIw(address, instruction);

opEnter: return decodeEnter(address, instruction);
opLeave: return decodeGeneric(instruction);
opRetfIw: return decodeGenericImmediate16(address, instruction);
opRetf: return decodeGeneric(instruction);
opInt3: return decodeGeneric(instruction);
opIntIb: return decodeGenericImmediate8(address, instruction);
opInto: return decodeGeneric(instruction);
opIret: return decodeGeneric(instruction);

opGrpRmb1: return decodeGenericModRm(address, instruction);
opGrpRmw1: return decodeGenericModRm(address, instruction);
opGrpRmbCl: return decodeGenericModRm(address, instruction);
opGrpRmwCl: return decodeGenericModRm(address, instruction);
opAam: return decodeGenericImmediate8(address, instruction);
opAad: return decodeGenericImmediate8(address, instruction);
opXlat: return decodeGeneric(instruction);
opXlat2: return decodeGeneric(instruction);

opFadd: return decodeGenericModRm(address, instruction);
opFcos: return decodeGenericModRm(address, instruction);
opFiadd: return decodeGenericModRm(address, instruction);
opFist: return decodeGenericModRm(address, instruction);
opFsub: return decodeGenericModRm(address, instruction);
opFst: return decodeGenericModRm(address, instruction);
opFmulp: return decodeGenericModRm(address, instruction);
Fnstsw: return decodeGenericModRm(address, instruction);

opLoopnz: return decodeGenericImmediate8(address, instruction);
opLoopz: return decodeGenericImmediate8(address, instruction);
opLoop: return decodeGenericImmediate8(address, instruction);
opJcxz: return decodeGenericImmediate8(address, instruction);
opInAlIb: return decodeGenericImmediate8(address, instruction);
opEaxIb: return decodeGenericImmediate8(address, instruction);
opOutIbAl: return decodeGenericImmediate8(address, instruction);
opOutIbEax: return decodeGenericImmediate8(address, instruction);

opCallIw: return decodeGenericImmediate16(address, instruction);
opJmp: return decodeGenericImmediate16(address, instruction);
opJmpFar: return decodeCall(address, instruction);
opJmpShort: return decodeGenericImmediate8(address, instruction);
opInAlEdx: return decodeGeneric(instruction);
opInEaxEdx: return decodeGeneric(instruction);
opOutEdxAl: return decodeGeneric(instruction);
opOutEdxEax: return decodeGeneric(instruction);

opLock: return decodeGeneric(instruction);
opHlt: return decodeGeneric(instruction);
opCmc: return decodeGeneric(instruction);
opGrpIb3: return decodeGrp3Ib(address, instruction);
opGrpIw3: return decodeGrp3Iw(address, instruction);

opClc: return decodeGeneric(instruction);
opStc: return decodeGeneric(instruction);
opCli: return decodeGeneric(instruction);
opSti: return decodeGeneric(instruction);
opCld: return decodeGeneric(instruction);
opStd: return decodeGeneric(instruction);
opGrp4: return decodeGenericModRm(address, instruction);
opGrp5: return decodeGenericModRm(address, instruction);

error:
    ERR("invalid decode opcode: %d", instruction->opcode);
}

inline void Decoder::decodeModRm(uint32_t& address, Instruction* instruction) {
    static uint8_t modrm;
    static uint8_t mod;

    modrm = ram->buffer[address++];
    mod = (modrm & 0b00000111);
    instruction->reg  = (modrm & 0b00111000) >> 3;

    switch(modrm & 0b11000000) {
    case 0b00000000:
        instruction->registerAddressing = false;

        /*thanks intel*/
        if(mod == 0b110) {
            instruction->displacement = ram->read16(address);
            instruction->base = 0b1000; //ZERO
            instruction->index = 0b1000; //ZERO
            instruction->length += 2;
        } else {
            instruction->displacement = 0;
            instruction->base = baseRegisterTable[mod];
            instruction->index = indexRegisterTable[mod];
        }
        break;
    case 0b01000000:
        instruction->registerAddressing = false;
        instruction->base = baseRegisterTable[mod];
        instruction->index = indexRegisterTable[mod];
        instruction->displacement = ram->read8(address);
        instruction->length += 1;
        break;
    case 0b10000000:
        instruction->registerAddressing = false;
        instruction->base = baseRegisterTable[mod];
        instruction->index = indexRegisterTable[mod];
        instruction->displacement = ram->read16(address);
        instruction->length += 2;
        break;
    case 0b11000000:
        instruction->registerAddressing = true;
        instruction->base = mod;
        break;
    }
}

inline void Decoder::decodeGeneric(Instruction *instruction) {
    instruction->length += 1;
}

inline void Decoder::decodeGenericModRm(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeGenericImmediate8(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    instruction->immediate = ram->read8(address);
}

inline void Decoder::decodeGenericImmediate16(uint32_t& address, Instruction *instruction) {
    instruction->length += 3;
    instruction->immediate = ram->read16(address);
}

inline void Decoder::decodeImulIw(uint32_t &address, Instruction *instruction) {
    instruction->length += 4;
    decodeModRm(address, instruction);
    instruction->immediate = ram->read16(address);
}

inline void Decoder::decodeImulIb(uint32_t &address, Instruction *instruction) {
    instruction->length += 3;
    decodeModRm(address, instruction);
    instruction->immediate = ram->read8(address);
}

inline void Decoder::decodeGrpRmbIb(uint32_t& address, Instruction *instruction) {
    instruction->length += 3;
    decodeModRm(address, instruction);
    instruction->immediate = ram->read8(address);
}

inline void Decoder::decodeGrpRmwIw(uint32_t& address, Instruction *instruction) {
    instruction->length += 4;
    decodeModRm(address, instruction);
    instruction->immediate = ram->read16(address);
}

inline void Decoder::decodeCall(uint32_t &address, Instruction *instruction) {
    instruction->length += 5;

    instruction->immediate = ram->read16(address);
    instruction->displacement = ram->read16(address + 2);
}

inline void Decoder::decodeEnter(uint32_t &address, Instruction *instruction) {
    instruction->length += 4;
    instruction->immediate = ram->read16(address);
    instruction->displacement = ram->read8(address + 2);
}

inline void Decoder::decodeGrp3Ib(uint32_t &address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);

    /*thanks intel*/
    if(instruction->reg < 2) {
        instruction->length += 1;
        instruction->immediate = ram->read8(address);
    }
}

inline void Decoder::decodeGrp3Iw(uint32_t &address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);

    /*thanks intel*/
    if(instruction->reg < 2) {
        instruction->length += 2;
        instruction->immediate = ram->read16(address);
    }
}


#endif // DECODER_H
