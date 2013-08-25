#ifndef DECODER_H
#define DECODER_H

#include "common.h"
#include "mem/ram.h"
#include "instruction.h"

class Decoder {
private:
    Ram* ram;

    static bool* buildPrefixTable();
    static uint8_t* buildPrefixEquivalenceTable();

    void decodePrefix(uint32_t& address, Instruction *instructon);
    void decodeInstruction(uint32_t& address, Instruction *instructon);

    void decodeModRm(uint32_t& address, Instruction* instruction);

    void decodeAddRmbRb(uint32_t& address, Instruction *instruction);
    void decodeAddRmwRw(uint32_t& address, Instruction *instruction);
    void decodeAddRbRmb(uint32_t& address, Instruction *instruction);
    void decodeAddRwRmw(uint32_t& address, Instruction *instruction);
    void decodeAddAlIb(uint32_t& address, Instruction *instruction);
    void decodeAddAxIw(uint32_t& address, Instruction *instruction);

public:
    Decoder(Ram* ram);

    void decode(uint32_t address, Instruction* instruction);
};

inline void Decoder::decode(uint32_t address, Instruction *instruction) {
    decodePrefix(address, instruction);
    decodeInstruction(address, instruction);
}

inline void Decoder::decodePrefix(uint32_t& address, Instruction *instructon) {
    static bool* prefixTable = buildPrefixTable();
    static uint8_t* prefixEqTable = buildPrefixEquivalenceTable();

    instructon->prefixMask = 0;

    while(prefixTable[ram->buffer[address]]) {
        instructon->prefixMask |= prefixEqTable[prefixTable[ram->buffer[address]]];
        address++;
    }
}

inline void Decoder::decodeInstruction(uint32_t& address, Instruction *instruction) {
    static const void * jumpTable[] = {
        /*0x00*/ &&opAddRmbRb, &&opAddRmwRw, &&opAddRbRmb, &&opAddRwRmw, &&opAddAlIb, &&opAddAxIw
    };

    goto *jumpTable[address++];

opAddRmbRb:
    decodeAddRmbRb(address, instruction);
opAddRmwRw:
    decodeAddRmwRw(address, instruction);
opAddRbRmb:
    decodeAddRbRmb(address, instruction);
opAddRwRmw:
    decodeAddRwRmw(address, instruction);
opAddAlIb:
    decodeAddAlIb(address, instruction);
opAddAxIw:
    decodeAddAxIw(address, instruction);
end:
    return;
}

inline void Decoder::decodeModRm(uint32_t& address, Instruction* instruction) {
    static uint8_t modrm;

    modrm = ram->buffer[address++];
    instruction->reg  = (modrm & 0b00111000) >> 3;
    instruction->base = (modrm & 0b00000111);

    switch(modrm & 0b11000000) {
    case 0b00000000:
        instruction->registerAddressing = false;

        /*thanks intel*/
        if(instruction->base == 0b101) {
            instruction->displacement = ram->read16(address++);
        }
        break;
    case 0b01000000:
        instruction->registerAddressing = false;
        instruction->displacement = ram->read8(address++);
        break;
    case 0b10000000:
        instruction->registerAddressing = false;
        instruction->displacement = ram->read16(address++);
        break;
    case 0b11000000:
        instruction->registerAddressing = true;
        break;
    }

}

inline void Decoder::decodeAddRmbRb(uint32_t& address, Instruction *instruction) {
    instruction->opcode = 0x00;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAddRmwRw(uint32_t& address, Instruction *instruction) {

}

inline void Decoder::decodeAddRbRmb(uint32_t& address, Instruction *instruction) {

}

inline void Decoder::decodeAddRwRmw(uint32_t& address, Instruction *instruction) {

}

inline void Decoder::decodeAddAlIb(uint32_t& address, Instruction *instruction) {

}

inline void Decoder::decodeAddAxIw(uint32_t& address, Instruction *instruction) {

}

#endif // DECODER_H
