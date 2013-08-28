#ifndef REGISTER16_H
#define REGISTER16_H

#include <stdint.h>

class FlagsRegister {
private:
    uint16_t operand1;
    uint16_t operand2;
    uint16_t result;
    uint8_t instruction;
public:
    void set(uint16_t operand1, uint16_t operand2, uint16_t result, uint8_t instruction);
};

inline void FlagsRegister::set(uint16_t operand1, uint16_t operand2, uint16_t result, uint8_t instruction) {
    this->operand1 = operand1;
    this->operand2 = operand2;
    this->result = result;
    this->instruction = instruction;
}

class Register16
{
public:
    uint16_t data;

    Register16();
};

#endif // REGISTER16_H
