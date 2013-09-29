#ifndef PORTHANDLER_H
#define PORTHANDLER_H

#include "common.h"
#include "config.h"

class PortHandler
{

    static const uint16_t PORT_RANGE = 0xFFFF;

private:
    void (*writeHandlers[PORT_RANGE])(uint16_t port, uint8_t value);
    uint8_t (*readHandlers[PORT_RANGE])(uint16_t port);

    static void dummyWriter(uint16_t port, uint8_t value);
    static uint8_t dummyReader(uint16_t port);
public:
    PortHandler();

    uint8_t in8(uint16_t port);
    uint16_t in16(uint16_t port);

    void out8(uint16_t port, uint8_t value);
    void out16(uint16_t port, uint16_t value);

    void registerWriter(uint16_t port, void (*handler)(uint16_t port, uint8_t value));
    void registerReader(uint16_t port, uint8_t (*handler)(uint16_t));
};

#endif // PORTHANDLER_H
