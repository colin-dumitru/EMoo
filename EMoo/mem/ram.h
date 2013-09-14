#ifndef RAM_H
#define RAM_H

#include "config.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

class Ram
{

private:

public:
    Ram();

    uint8_t buffer[RAM_SIZE];

    void loadFromFile(const char *filename, uint32_t address);
    void write(uint32_t address, uint8_t* source, uint32_t length);

    uint8_t read8(uint8_t address);
    uint16_t read16(uint8_t address);
};

inline uint8_t Ram::read8(uint8_t address) {
    return buffer[address];
}

inline uint16_t Ram::read16(uint8_t address) {
    return *((uint16_t*)(buffer + address));
}

#endif // RAM_H
