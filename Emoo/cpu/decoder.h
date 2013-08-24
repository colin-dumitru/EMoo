#ifndef DECODER_H
#define DECODER_H

#include "common.h"
#include "instruction.h"

class Decoder {
private:
    static bool* buildPrefixTable();

    void decodePrefix(uint32_t& address, Instruction *instructon);
    void decodeInstruction(uint32_t& address, Instruction *instructon);

    void decodeModRm(uint32_t address, Instruction* instruction);

    void decodeAddRmbRb(uint32_t& address, Instruction *instruction);
    void decodeAddRmwRw(uint32_t& address, Instruction *instruction);
    void decodeAddRbRmb(uint32_t& address, Instruction *instruction);
    void decodeAddRwRmw(uint32_t& address, Instruction *instruction);
    void decodeAddAlIb(uint32_t& address, Instruction *instruction);
    void decodeAddAxIw(uint32_t& address, Instruction *instruction);

public:
    Decoder();

    void decode(uint32_t address, Instruction* instruction);
};

inline void Decoder::decodePrefix(uint32_t& address, Instruction *instructon) {
    instructon->prefixMask = 0;

}

inline void Decoder::decodeInstruction(uint32_t& address, Instruction *instruction) {
    static const void * jumoTable[] = {
        /*0x00*/ &&opAddRmbRb, &&opAddRmwRw, &&opAddRbRmb, &&opAddRwRmw, &&opAddAlIb, &&opAddAxIw
    };

    //todo goto

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

inline void Decoder::decodeModRm(uint32_t address, Instruction* instruction) {

}

inline void Decoder::decode(uint32_t address, Instruction *instruction) {
    decodePrefix(address, instruction);
    decodeInstruction(address, instruction);
}

inline void Decoder::decodeAddRmbRb(uint32_t& address, Instruction *instruction) {
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
