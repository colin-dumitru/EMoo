#include "keyboard.h"

Keyboard::Keyboard()
{
}

uint8_t Keyboard::inputBuffer = 0;

uint8_t Keyboard::read60(uint16_t) {
    return inputBuffer;
}

void Keyboard::write60(uint16_t port, uint8_t value) {

}
