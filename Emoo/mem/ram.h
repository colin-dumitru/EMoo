#ifndef RAM_H
#define RAM_H

#include "config.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

class Ram
{

private:

public:
    Ram();

    uint8_t buffer[RAM_SIZE];

    void loadFromFile(char* filename, uint8_t address);
};

#endif // RAM_H
