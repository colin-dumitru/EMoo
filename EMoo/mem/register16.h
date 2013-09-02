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
        ADD = 0b1000000000000000,
        ADC = 0b0100000000000000,
        SUB = 0b0010000000000000,
        SBB = 0b0001000000000000,
        INC = 0b0000100000000000,
        DEC = 000000010000000000,
        NEG = 000000001000000000,
        LOG = 0b0000000100000000
    };

    enum Size {
        BIT8 = 0b0000000000000010,
        BIT16 = 0b0000000000000001
    };

    const static uint16_t ADD8 = (uint16_t)ADD | BIT8;
    const static uint16_t ADC8 = (uint16_t)ADC | BIT8;
    const static uint16_t SUB8 = (uint16_t)SUB | BIT8;
    const static uint16_t SBB8 = (uint16_t)SBB | BIT8;
    const static uint16_t INC8 = (uint16_t)INC | BIT8;
    const static uint16_t DEC8 = (uint16_t)DEC | BIT8;
    const static uint16_t NEG8 = (uint16_t)NEG | BIT8;
    const static uint16_t LOG8 = (uint16_t)LOG | BIT8;

    const static uint16_t ADD16 = (uint16_t)ADD | BIT16;
    const static uint16_t ADC16 = (uint16_t)ADC | BIT16;
    const static uint16_t SUB16 = (uint16_t)SUB | BIT16;
    const static uint16_t SBB16 = (uint16_t)SBB | BIT16;
    const static uint16_t INC16 = (uint16_t)INC | BIT16;
    const static uint16_t DEC16 = (uint16_t)DEC | BIT16;
    const static uint16_t NEG16 = (uint16_t)NEG | BIT16;
    const static uint16_t LOG16 = (uint16_t)LOG | BIT16;

    static const uint16_t INSTRUCTION_MASK = 0b1111111111111100;
    static const uint16_t SIZE_MASK        = 0b0000000000000011;

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

#endif // REGISTER16_H
