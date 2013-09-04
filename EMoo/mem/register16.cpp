#include "register16.h"

Register16::Register16()
{
}

const bool FlagsRegister::PARITY_TABLE[256] = {
    false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    false, true, true, false, true, false, false, true, true, false, false, true, false, true, true, false,
    true, false, false, true, false, true, true, false, false, true, true, false, true, false, false, true
};

bool FlagsRegister::getZf() {
    return result == 0;
}

bool FlagsRegister::getPf() {
    return PARITY_TABLE[(uint8_t)result];
}

bool FlagsRegister::getSf() {
    switch(instruction & SIZE_MASK) {
    case BIT8:
        return result >= 0x80;
    case BIT16:
        return result >= 0x8000;
    }
    ERR("Invalid sf size");
    return false;
}

bool FlagsRegister::getCf() {
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
        return operand1 != 0;
    }
    return false;
}

bool FlagsRegister::getAf() {

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
        return operand2 != 0;
    }
    return false;
}

bool FlagsRegister::getOf() {
    switch (instruction & INSTRUCTION_MASK) {
    case ADD:
    case ADC:
        return ((~(operand1 ^ operand2) & (operand2 ^ result)) & 0x80000000) != 0;
    case SUB:
    case SBB:
        return (((operand1 ^ operand2) & (operand1 ^ result)) & 0x80000000) != 0;
    case NEG:
    case INC:
        if((instruction & SIZE_MASK) == BIT8) {
            return (result & 0xFF) == 0x80;
        } else {
            return result == 0x8000;
        }
    case DEC:
        if(instruction == DEC8) {
            return (result & 0xFF) == 0x7F;
        } else {
            return result == 0x7FFF;
        }
    }
    return false;
}
