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
        /*0x38*/ &&opCmpRmbRb, &&opCmpRmwRw, &&opCmpRbRmb, &&opCmpRwRmw, &&opCmpAlIb, &&opCmpAxIw, &&error, &&opAas
        /*0x40*/
        /*0x48*/
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
    instruction->displacement = ram->read8(address);
}

inline void Decoder::decodeGenericImmediate16(uint32_t& address, Instruction *instruction) {
    instruction->length += 3;
    instruction->displacement = ram->read16(address);
}

#endif // DECODER_H
