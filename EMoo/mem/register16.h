#ifndef REGISTER16_H
#define REGISTER16_H

#include <stdint.h>
#include "common.h"

class FlagsRegister {

private:
    static const bool PARITY_TABLE[256];
public:
    enum Instruction {
        ADD  = 0x01,
        ADC  = 0x02,
        SUB  = 0x03,
        SBB  = 0x04,
        INC  = 0x05,
        DEC  = 0x06,
        NEG  = 0x07,
        LOG  = 0x08,
        DAA  = 0x09,
        IMUL = 0x0A,
        POPF = 0x0B,
        /*
        result is the last result needed by ZF, PF, SF; operand1 is the AUX flag; operand 2 is the result of the rotate
        ROL
        CF = RES & 1
        OF = MSB(RES) ^ LSB(RES)

        ROR
        CF = MSB(RES)
        OF = MSB(RES) ^ MSB-1(RES)

        RCL
        RES >> 1
        CF = MSB(RES)
        OF = MSB(RES) ^ MSB-1(RES)

        RCR
        RES >> 1
        CF = MSB(RES)
        OF = MSB-1(RES) ^ MSB-2(RES)
        */
        ROL  = 0x0C,
        ROR  = 0x0D,
        RCL  = 0x0E,
        RCR  = 0x0F,

        /*result is the result of the shift, operand1 is the result of the shift one step behind*/
        SHL  = 0x10,
        SHR  = 0x11,

        /*result is the last result stored, LSB(operand1) = AF, LSB+1(operand1) = OF, operand2 = CF*/
        CMC  = 0x12,
        MUL  = 0x13,

        /*operand1 is the AF flag, operand2 is the OF, result is the last result*/
        CLC  = 0x14,
        STC  = 0x15
    };

    enum Size {
        BIT8  = 0b0000000000000000,
        BIT16 = 0b1000000000000000
    };

    const static uint16_t ADD8  = (uint16_t)ADD | BIT8;
    const static uint16_t ADC8  = (uint16_t)ADC | BIT8;
    const static uint16_t SUB8  = (uint16_t)SUB | BIT8;
    const static uint16_t SBB8  = (uint16_t)SBB | BIT8;
    const static uint16_t INC8  = (uint16_t)INC | BIT8;
    const static uint16_t DEC8  = (uint16_t)DEC | BIT8;
    const static uint16_t NEG8  = (uint16_t)NEG | BIT8;
    const static uint16_t LOG8  = (uint16_t)LOG | BIT8;
    const static uint16_t DAA8  = (uint16_t)DAA | BIT8;
    const static uint16_t IMUL8 = (uint16_t)IMUL | BIT8;
    const static uint16_t SHL8  = (uint16_t)SHL  | BIT8;
    const static uint16_t SHR8  = (uint16_t)SHR  | BIT8;
    const static uint16_t MUL8  = (uint16_t)MUL  | BIT8;

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
    const static uint16_t SHL16  = (uint16_t)SHL  | BIT16;
    const static uint16_t SHR16  = (uint16_t)SHR  | BIT16;
    const static uint16_t MUL16  = (uint16_t)MUL  | BIT16;

    static const uint16_t INSTRUCTION_MASK = 0b0111111111111111;
    static const uint16_t SIZE_MASK        = 0b1000000000000000;

    uint16_t operand1;
    uint16_t operand2;
    uint16_t result;
    uint16_t instruction;

    bool df;
    bool tf;
    bool itf;

    FlagsRegister();

    void set(uint16_t operand1, uint16_t operand2, uint16_t result, uint16_t instruction);
    void set(uint16_t result, uint16_t instruction);
    void set(uint16_t instruction);

    bool getZf();
    bool getPf();
    bool getSf();
    bool getCf();
    bool getAf();
    bool getOf();

    uint16_t toWord();
    void fromWord(uint16_t value);

    uint8_t toByte();
    void fromByte(uint8_t value);
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

inline void FlagsRegister::set(uint16_t instruction) {
    this->instruction = instruction;
}

class Register16
{
public:
    uint16_t data;

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
        return result & 0x80;
    case BIT16:
        return result & 0x8000;
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
        return (result & 0xFF00) != 0 && (result & 0xFF00) != 0xFF00;
    case POPF:
        return operand1 & 1;
    case ROL:
        return operand2 & 1;
    case ROR:
        return operand2 & 0x8000;
    case RCL:
        return operand2 & 0x8000;
    case RCR:
        return operand2 & 0x8000;
    case SHL:
        if(instruction == SHL8) {
            return operand1 & 0x80;
        } else {
            return operand1 & 0x8000;
        }
    case SHR:
        return operand1 & 1;
    case CMC:
        return operand2;
    case MUL:
        if(instruction == MUL8) {
            return result & 0xFF00;
        } else {
            return result;
        }
    case CLC:
        return false;
    case STC:
        return true;
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
        return operand1 & 16 /*1 << 4*/;
    case ROL:
    case ROR:
    case RCL:
    case RCR:
        return operand1;
    case CMC:
        return operand1 & 1;
    case CLC:
    case STC:
        return operand1;
    }
    return false;
}

inline bool FlagsRegister::getOf() {
    switch (instruction & INSTRUCTION_MASK) {
    case ADD:
    case ADC:
        if ((instruction & SIZE_MASK) == BIT8) {
            return ((~(operand1 ^ operand2) & (operand2 ^ result)) & 0x80) != 0;
        } else {
            return ((~(operand1 ^ operand2) & (operand2 ^ result)) & 0x8000) != 0;
        }
    case SUB:
    case SBB:
        if ((instruction & SIZE_MASK) == BIT8) {
            return (((operand1 ^ operand2) & (operand1 ^ result)) & 0x80) != 0;
        } else {
            return (((operand1 ^ operand2) & (operand1 ^ result)) & 0x8000) != 0;
        }
    case NEG:
    case INC:
        return result == 0x8000;
    case DEC:
        return result == 0x7FFF;
    case IMUL:
        return result;
    case POPF:
        return operand1 & 2048 /*1 << 11*/;
    case ROL:
        return (operand2 & 1) ^ (operand2 >> 15);
    case ROR:
        return (operand2 ^ (operand2 << 1)) & 0x7FFF;
    case RCL:
        return (operand2 ^ (operand2 << 1)) & 0x7FFF;
    case RCR:
        return (operand2 ^ (operand2 << 1)) & 0xBFFF;
    case SHL:
        if(instruction == SHL8) {
            return (result ^ operand1) & 0x80;
        } else {
            return (result ^ operand1) & 0x8000;
        }
    case SHR:
        if(instruction == SHL8) {
            return operand1 & 0x80;
        } else {
            return operand1 & 0x8000;
        }
    case CMC:
        return operand1 & 2;
    case MUL:
        if(instruction == MUL8) {
            return result & 0xFF00;
        } else {
            return result;
        }
    case CLC:
    case STC:
        return operand2;
    }
    return false;
}

inline uint16_t FlagsRegister::toWord() {
    return 2 |
            (uint16_t)getCf() |
            ((uint16_t)getPf() << 2) |
            ((uint16_t)getAf() << 4) |
            ((uint16_t)getZf() << 6) |
            ((uint16_t)getSf() << 7) |
            ((uint16_t)tf << 8) |
            ((uint16_t)itf << 9) |
            ((uint16_t)df << 10) |
            ((uint16_t)getOf() << 11);
}

inline void FlagsRegister::fromWord(uint16_t value) {
    static const uint16_t resultTable[] = {
        1, 0, 0, 0,
        0x8001, 0x8000, 0, 0
    };

    tf = (value & 256 /*1 << 8*/) != 0;
    itf = (value & 512 /*1 << 9*/) != 0;
    df = (value & 1024 /*1 << 10*/) != 0;

    /*00 01 02*/
    /*PF ZF SF*/
    operand2 =
            ((value & 4 /*1 << 2*/ ) >> 2) |
            ((value & 64 /*1 << 6*/ ) >> 5) |
            ((value & 128 /*1 << 7*/ ) >> 5);

    operand1 = value;
    result = resultTable[operand2];
    instruction = FlagsRegister::POPF16;
}

inline uint8_t FlagsRegister::toByte() {
    return 2 |
            (uint16_t)getCf() |
            ((uint16_t)getPf() << 2) |
            ((uint16_t)getAf() << 4) |
            ((uint16_t)getZf() << 6) |
            ((uint16_t)getSf() << 7);
}

inline void FlagsRegister::fromByte(uint8_t value) {
    static const uint16_t resultTable[] = {
        1, 0, 0, 0,
        0x8001, 0x8000, 0, 0
    };

    /*00 01 02*/
    /*PF ZF SF*/
    operand2 =
            ((value & 4 /*1 << 2*/ ) >> 2) |
            ((value & 64 /*1 << 6*/ ) >> 5) |
            ((value & 128 /*1 << 7*/ ) >> 5);

    operand1 = value;
    result = resultTable[operand2];
    instruction = FlagsRegister::POPF16;
}


#endif // REGISTER16_H
