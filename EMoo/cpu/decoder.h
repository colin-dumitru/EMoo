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

    void decodeAddRmbRb(uint32_t& address, Instruction *instruction);
    void decodeAddRmwRw(uint32_t& address, Instruction *instruction);
    void decodeAddRbRmb(uint32_t& address, Instruction *instruction);
    void decodeAddRwRmw(uint32_t& address, Instruction *instruction);
    void decodeAddAlIb(uint32_t& address, Instruction *instruction);
    void decodeAddAxIw(uint32_t& address, Instruction *instruction);

    void decodePushEs(Instruction *instruction);
    void decodePopEs(Instruction *instruction);

    void decodeOrRmbRb(uint32_t& address, Instruction *instruction);
    void decodeOrRmwRw(uint32_t& address, Instruction *instruction);
    void decodeOrRbRmb(uint32_t& address, Instruction *instruction);
    void decodeOrRwRmw(uint32_t& address, Instruction *instruction);
    void decodeOrAlIb(uint32_t& address, Instruction *instruction);
    void decodeOrAxIw(uint32_t& address, Instruction *instruction);

    void decodePushCs(Instruction *instruction);
    void decodePopCs(Instruction *instruction);

    void decodeAdcRmbRb(uint32_t& address, Instruction *instruction);
    void decodeAdcRmwRw(uint32_t& address, Instruction *instruction);
    void decodeAdcRbRmb(uint32_t& address, Instruction *instruction);
    void decodeAdcRwRmw(uint32_t& address, Instruction *instruction);
    void decodeAdcAlIb(uint32_t& address, Instruction *instruction);
    void decodeAdcAxIw(uint32_t& address, Instruction *instruction);

    void decodePushSs(Instruction *instruction);
    void decodePopSs(Instruction *instruction);

    void decodeSbbRmbRb(uint32_t& address, Instruction *instruction);
    void decodeSbbRmwRw(uint32_t& address, Instruction *instruction);
    void decodeSbbRbRmb(uint32_t& address, Instruction *instruction);
    void decodeSbbRwRmw(uint32_t& address, Instruction *instruction);
    void decodeSbbAlIb(uint32_t& address, Instruction *instruction);
    void decodeSbbAxIw(uint32_t& address, Instruction *instruction);

    void decodePushDs(Instruction *instruction);
    void decodePopDs(Instruction *instruction);

    void decodeAndRmbRb(uint32_t& address, Instruction *instruction);
    void decodeAndRmwRw(uint32_t& address, Instruction *instruction);
    void decodeAndRbRmb(uint32_t& address, Instruction *instruction);
    void decodeAndRwRmw(uint32_t& address, Instruction *instruction);
    void decodeAndAlIb(uint32_t& address, Instruction *instruction);
    void decodeAndAxIw(uint32_t& address, Instruction *instruction);

    void decodeDaa(Instruction *instruction);

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
        /*0x20*/ &&opAndRmbRb, &&opAndRmwRw, &&opAndRbRmb, &&opAndRwRmw, &&opAndAlIb, &&opAndAxIw, &&error, &&opDaa
        /*0x28*/
        /*0x30*/
        /*0x38*/
        /*0x40*/
        /*0x48*/
    };

    instruction->opcode = ram->buffer[address++];
    goto *jumpTable[instruction->opcode];

opAddRmbRb: return decodeAddRmbRb(address, instruction);
opAddRmwRw: return decodeAddRmwRw(address, instruction);
opAddRbRmb: return decodeAddRbRmb(address, instruction);
opAddRwRmw: return decodeAddRwRmw(address, instruction);
opAddAlIb: return decodeAddAlIb(address, instruction);
opAddAxIw: return decodeAddAxIw(address, instruction);

opPushEs: return decodePushEs(instruction);
opPopEs: return decodePopEs(instruction);

opOrRmbRb: return decodeOrRmbRb(address, instruction);
opOrRmwRw: return decodeOrRmwRw(address, instruction);
opOrRbRmb: return decodeOrRbRmb(address, instruction);
opOrRwRmw: return decodeOrRwRmw(address, instruction);
opOrAlIb: return decodeOrAlIb(address, instruction);
opOrAxIw: return decodeOrAxIw(address, instruction);

opPushCs: return decodePushCs(instruction);
opPopCs: return decodePopCs(instruction);

opAdcRmbRb: return decodeAdcRmbRb(address, instruction);
opAdcRmwRw: return decodeAdcRmwRw(address, instruction);
opAdcRbRmb: return decodeAdcRbRmb(address, instruction);
opAdcRwRmw: return decodeAdcRwRmw(address, instruction);
opAdcAlIb: return decodeAdcAlIb(address, instruction);
opAdcAxIw: return decodeAdcAxIw(address, instruction);

opPushSs: return decodePushSs(instruction);
opPopSs: return decodePopSs(instruction);

opSbbRmbRb: return decodeSbbRmbRb(address, instruction);
opSbbRmwRw: return decodeSbbRmwRw(address, instruction);
opSbbRbRmb: return decodeSbbRbRmb(address, instruction);
opSbbRwRmw: return decodeSbbRwRmw(address, instruction);
opSbbAlIb: return decodeSbbAlIb(address, instruction);
opSbbAxIw: return decodeSbbAxIw(address, instruction);

opPushDs: return decodePushDs(instruction);
opPopDs: return decodePopDs(instruction);

opAndRmbRb: return decodeAndRmbRb(address, instruction);
opAndRmwRw: return decodeAndRmwRw(address, instruction);
opAndRbRmb: return decodeAndRbRmb(address, instruction);
opAndRwRmw: return decodeAndRwRmw(address, instruction);
opAndAlIb: return decodeAndAlIb(address, instruction);
opAndAxIw: return decodeAndAxIw(address, instruction);

opDaa: return decodeDaa(instruction);

error:
    ERR("invalid decode opcode: %d", instruction->opcode);
    return;
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

inline void Decoder::decodeAddRmbRb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAddRmwRw(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAddRbRmb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAddRwRmw(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAddAlIb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    instruction->displacement = ram->read8(address);
}

inline void Decoder::decodeAddAxIw(uint32_t& address, Instruction *instruction) {
    instruction->length += 3;
    instruction->displacement = ram->read16(address);
}

inline void Decoder::decodePushEs(Instruction *instruction) {
    instruction->length += 1;
}

inline void Decoder::decodePopEs(Instruction *instruction) {
    instruction->length += 1;
}

inline void Decoder::decodeOrRmbRb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeOrRmwRw(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeOrRbRmb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeOrRwRmw(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeOrAlIb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    instruction->displacement = ram->read8(address);
}

inline void Decoder::decodeOrAxIw(uint32_t& address, Instruction *instruction) {
    instruction->length += 3;
    instruction->displacement = ram->read16(address);
}

inline void Decoder::decodePushCs(Instruction *instruction) {
    instruction->length += 1;
}

inline void Decoder::decodePopCs(Instruction *instruction) {
    instruction->length += 1;
}

inline void Decoder::decodeAdcRmbRb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAdcRmwRw(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAdcRbRmb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAdcRwRmw(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAdcAlIb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    instruction->displacement = ram->read8(address);
}

inline void Decoder::decodeAdcAxIw(uint32_t& address, Instruction *instruction) {
    instruction->length += 3;
    instruction->displacement = ram->read16(address);
}

inline void Decoder::decodePushSs(Instruction *instruction) {
    instruction->length += 1;
}

inline void Decoder::decodePopSs(Instruction *instruction) {
    instruction->length += 1;
}

inline void Decoder::decodeSbbRmbRb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeSbbRmwRw(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeSbbRbRmb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeSbbRwRmw(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeSbbAlIb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    instruction->displacement = ram->read8(address);
}

inline void Decoder::decodeSbbAxIw(uint32_t& address, Instruction *instruction) {
    instruction->length += 3;
    instruction->displacement = ram->read16(address);
}

inline void Decoder::decodePushDs(Instruction *instruction) {
    instruction->length += 1;
}

inline void Decoder::decodePopDs(Instruction *instruction) {
    instruction->length += 1;
}

inline void Decoder::decodeAndRmbRb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAndRmwRw(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAndRbRmb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAndRwRmw(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAndAlIb(uint32_t& address, Instruction *instruction) {
    instruction->length += 2;
    instruction->displacement = ram->read8(address);
}

inline void Decoder::decodeAndAxIw(uint32_t& address, Instruction *instruction) {
    instruction->length += 3;
    instruction->displacement = ram->read16(address);
}

inline void Decoder::decodeDaa(Instruction *instruction) {
    instruction->length += 1;
}

#endif // DECODER_H
