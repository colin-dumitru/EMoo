#ifndef INTERRUPTHANDLER_H
#define INTERRUPTHANDLER_H

#include "config.h"
#include "common.h"


class InterruptHandler
{
public:
    InterruptHandler();

    void call(uint8_t interrupt);
};

#endif // INTERRUPTHANDLER_H
