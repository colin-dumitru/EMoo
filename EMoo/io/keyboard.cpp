#include "keyboard.h"

Keyboard::Keyboard()
{
}

uint8_t Keyboard::controllRegister = 0;
uint8_t Keyboard::inputBuffer = 0;

uint8_t Keyboard::read60(uint16_t port) {
    return inputBuffer;
}

void Keyboard::write60(uint16_t port, uint8_t value) {

}

uint8_t Keyboard::read61(uint16_t port) {
    return controllRegister;
}

void Keyboard::write61(uint16_t port, uint8_t value) {
    controllRegister = value;
}

uint8_t Keyboard::read62(uint16_t port) {

}

void Keyboard::write62(uint16_t port, uint8_t value) {

}

uint8_t Keyboard::read63(uint16_t port) {

}

void Keyboard::write63(uint16_t port, uint8_t value) {

}
