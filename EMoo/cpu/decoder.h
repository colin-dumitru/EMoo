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
        /*0x00*/ &&opAddRmbRb, &&opAddRmwRw, &&opAddRbRmb, &&opAddRwRmw, &&opAddAlIb, &&opAddAxIw
    };

    address += 1;
    goto *jumpTable[instruction->opcode];

opAddRmbRb:
    return decodeAddRmbRb(address, instruction);
opAddRmwRw:
    return decodeAddRmwRw(address, instruction);
opAddRbRmb:
    return decodeAddRbRmb(address, instruction);
opAddRwRmw:
    return decodeAddRwRmw(address, instruction);
opAddAlIb:
    return decodeAddAlIb(address, instruction);
opAddAxIw:
    return decodeAddAxIw(address, instruction);
end:
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
    instruction->opcode = 0x00;
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAddRmwRw(uint32_t& address, Instruction *instruction) {
    instruction->opcode = 0x01;
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAddRbRmb(uint32_t& address, Instruction *instruction) {
    instruction->opcode = 0x02;
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAddRwRmw(uint32_t& address, Instruction *instruction) {
    instruction->opcode = 0x03;
    instruction->length += 2;
    decodeModRm(address, instruction);
}

inline void Decoder::decodeAddAlIb(uint32_t& address, Instruction *instruction) {
    instruction->opcode = 0x04;
}

inline void Decoder::decodeAddAxIw(uint32_t& address, Instruction *instruction) {
    instruction->opcode = 0x05;
}

#endif // DECODER_H
