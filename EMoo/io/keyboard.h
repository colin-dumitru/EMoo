#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "common.h"

class Keyboard
{

private:
    /*Keyboard input is set to this buffer, and outputed to port 0x61*/
    static uint8_t inputBuffer;
    /*
     *option flags - port 0x61
     *
     bit 7	(1= IRQ 0 reset )
     bit 6-4    reserved
     bit 3 = 1  channel check enable
     bit 2 = 1  parity check enable
     bit 1 = 1  speaker data enable
     bit 0 = 1  timer 2 gate to speaker enable
    */
    static uint8_t controllRegister;
public:
    Keyboard();

    static uint8_t read60(uint16_t port);
    static void write60(uint16_t port, uint8_t value);

    static uint8_t read61(uint16_t port);
    static void write61(uint16_t port, uint8_t value);

    static uint8_t read62(uint16_t port);
    static void write62(uint16_t port, uint8_t value);

    static uint8_t read63(uint16_t port);
    static void write63(uint16_t port, uint8_t value);
};

#endif // KEYBOARD_H
