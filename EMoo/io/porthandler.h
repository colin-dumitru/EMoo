#ifndef PORTHANDLER_H
#define PORTHANDLER_H

#include "common.h"
#include "config.h"

class PortHandler
{
public:
    PortHandler();

    uint8_t in8(uint16_t port);
    uint8_t in16(uint16_t port);

    void out8(uint16_t port, uint8_t value);
    void out16(uint16_t port, uint8_t value);
};

#endif // PORTHANDLER_H
