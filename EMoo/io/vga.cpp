#include "vga.h"
#include "machine.h"

VGA::VGA()
{
}

uint8_t VGA::statusRegister = 1;

uint8_t VGA::readStatusRegister(uint16_t) {
    //return 0; //todo remove
    return statusRegister;
}

void VGA::writeStatusRegister(uint16_t port, uint8_t) {
    ERR("Unsuported IO port: %d", port);
}

void VGA::resetTiming() {
    lastTick = machine.timing.tick;
}

void VGA::updateTiming() {
    if (machine.timing.tick >= (lastTick + HREFRESH) ) {
        scanline = (scanline + 1) % 525;

        if (scanline > 479) {
            statusRegister = 8;
        } else {
            statusRegister = 0;
        }

        statusRegister |= scanline & 1;

        lastTick = machine.timing.tick;
    }
}
