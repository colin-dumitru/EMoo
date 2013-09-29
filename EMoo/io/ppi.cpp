#include "ppi.h"

PPI::PPI()
{
}

uint8_t PPI::controllRegister = 0;
uint8_t PPI::controllRegister2 = 0;
uint8_t PPI::commandRegister = 0;

uint8_t PPI::read61(uint16_t) {
    return controllRegister;
}

void PPI::write61(uint16_t, uint8_t value) {
    controllRegister = value;
}

uint8_t PPI::read62(uint16_t) {
    return controllRegister2;
}

void PPI::write62(uint16_t, uint8_t value) {
    controllRegister2 = value;
}

uint8_t PPI::read63(uint16_t) {
    return commandRegister;
}

void PPI::write63(uint16_t, uint8_t value) {
    commandRegister = value;
}
