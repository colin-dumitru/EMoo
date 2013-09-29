#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "common.h"

class Keyboard
{

private:
    /*Keyboard input is set to this buffer, and outputed to port 0x61*/
    static uint8_t inputBuffer;
public:
    Keyboard();

    static uint8_t read60(uint16_t port);
    static void write60(uint16_t port, uint8_t value);

};

#endif // KEYBOARD_H
