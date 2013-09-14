#ifndef REGISTER16_H
#define REGISTER16_H

#include <stdint.h>
#include "common.h"

class FlagsRegister {

private:
    static const bool PARITY_TABLE[256];

    uint16_t operand1;
    uint16_t operand2;
    uint16_t result;
    uint16_t instruction;
public:
    enum Instruction {
        ADD  = 0b1000000000000000,
        ADC  = 0b0100000000000000,
        SUB  = 0b0010000000000000,
        SBB  = 0b0001000000000000,
        INC  = 0b0000100000000000,
        DEC  = 000000010000000000,
        NEG  = 000000001000000000,
        LOG  = 0b0000000100000000,
        DAA  = 0b0000000010000000,
        IMUL = 0b0000000001000000,
        POPF = 0b0000000000100000
    };

    enum Size {
        BIT8  = 0b0000000000000010,
        BIT16 = 0b0000000000000001
    };

    const static uint16_t ADD8  = (uint16_t)ADD | BIT8;
    const static uint16_t ADC8  = (uint16_t)ADC | BIT8;
    const static uint16_t SUB8  = (uint16_t)SUB | BIT8;
    const static uint16_t SBB8  = (uint16_t)SBB | BIT8;
    const static uint16_t NEG8  = (uint16_t)NEG | BIT8;
    const static uint16_t LOG8  = (uint16_t)LOG | BIT8;
    const static uint16_t DAA8  = (uint16_t)DAA | BIT8;
    const static uint16_t IMUL8 = (uint16_t)IMUL | BIT8;

    const static uint16_t ADD16  = (uint16_t)ADD | BIT16;
    const static uint16_t ADC16  = (uint16_t)ADC | BIT16;
    const static uint16_t SUB16  = (uint16_t)SUB | BIT16;
    const static uint16_t SBB16  = (uint16_t)SBB | BIT16;
    const static uint16_t INC16  = (uint16_t)INC | BIT16;
    const static uint16_t DEC16  = (uint16_t)DEC | BIT16;
    const static uint16_t NEG16  = (uint16_t)NEG | BIT16;
    const static uint16_t LOG16  = (uint16_t)LOG | BIT16;
    const static uint16_t IMUL16 = (uint16_t)IMUL | BIT16;
    const static uint16_t POPF16 = (uint16_t)POPF | BIT16;

    static const uint16_t INSTRUCTION_MASK = 0b1111111111111100;
    static const uint16_t SIZE_MASK        = 0b0000000000000011;

    bool df;
    bool tf;
    bool itf;

    void set(uint16_t operand1, uint16_t operand2, uint16_t result, uint16_t instruction);
    void set(uint16_t result, uint16_t instruction);

    bool getZf();
    bool getPf();
    bool getSf();
    bool getCf();
    bool getAf();
    bool getOf();
};

inline void FlagsRegister::set(uint16_t operand1, uint16_t operand2, uint16_t result, uint16_t instruction) {
    this->operand1 = operand1;
    this->operand2 = operand2;
    this->result = result;
    this->instruction = instruction;
}

inline void FlagsRegister::set(uint16_t result, uint16_t instruction) {
    this->result = result;
    this->instruction = instruction;
}

class Register16
{
public:
    uint16_t data = 0;

    Register16();

    uint8_t low() {
        return LOW(data);
    }

    uint8_t high() {
        return HIGH(data);
    }
};


inline bool FlagsRegister::getZf() {
    return result == 0;
}

inline bool FlagsRegister::getPf() {
    return PARITY_TABLE[(uint8_t)result];
}

inline bool FlagsRegister::getSf() {
    switch(instruction & SIZE_MASK) {
    case BIT8:
        return result >= 0x80;
    case BIT16:
        return result >= 0x8000;
    }
    ERR("Invalid sf size");
    return false;
}

inline bool FlagsRegister::getCf() {
    switch (instruction & INSTRUCTION_MASK) {
    case ADD:
        return result < operand1;
    case ADC:
        return result <= operand1;
    case SUB:
        return operand1 < operand2;
    case SBB:
        if(instruction == SBB8) {
            return (operand1 < result) || ((operand2 & 0xFF) == 0xFF);
        } else {
            return (operand1 < result) || (operand2 == 0xFFFF);
        }

    case NEG:
        return (result != 0);
    case DAA:
        return operand1;
    case INC:
    case DEC:
        return operand2;
    case IMUL:
        return result;
    case POPF:
        return operand1 & 1;

    }
    return false;
}

inline bool FlagsRegister::getAf() {

    switch (instruction & INSTRUCTION_MASK) {
    case ADD:
    case ADC:
    case SUB:
    case SBB:
        return ((operand1 ^ operand2) ^ result) & 0x10;
    case NEG:
        return (result & 0xf) != 0;
    case INC:
        return (result & 0xf) == 0;
    case DEC:
        return (result & 0xf) == 0xf;
    case DAA:
        return operand2;
    case POPF:
        return (operand1 & 16 /*1 << 4*/) != 0;
    }
    return false;
}

inline bool FlagsRegister::getOf() {
    switch (instruction & INSTRUCTION_MASK) {
    case ADD:
    case ADC:
        return ((~(operand1 ^ operand2) & (operand2 ^ result)) & 0x8000) != 0;
    case SUB:
    case SBB:
        return (((operand1 ^ operand2) & (operand1 ^ result)) & 0x8000) != 0;
    case NEG:
    case INC:
        return result == 0x8000;
    case DEC:
        return result == 0x7FFF;
    case IMUL:
        return result;
    case POPF:
        return (operand1 & 2048 /*1 << 11*/) != 0;
    }
    return false;
}


#endif // REGISTER16_H
