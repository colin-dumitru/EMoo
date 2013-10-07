#ifndef VGA_H
#define VGA_H

#include "common.h"
#include "cpu/timing.h"

MACHINE_AWARE

class VGA
{
private:
    static const uint32_t HREFRESH = HOST_FREQ / 31500;

    static uint8_t statusRegister;

    uint16_t scanline;
    uint64_t lastTick;

public:
    VGA();

    void resetTiming();
    void updateTiming();

    /*port 3DA*/
    static uint8_t readStatusRegister(uint16_t port);
    static void writeStatusRegister(uint16_t port, uint8_t value);
};

#endif // VGA_H
