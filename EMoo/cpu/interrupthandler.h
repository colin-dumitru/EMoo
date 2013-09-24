#ifndef INTERRUPTHANDLER_H
#define INTERRUPTHANDLER_H

#include "config.h"
#include "common.h"

MACHINE_AWARE


class InterruptHandler
{
public:
    InterruptHandler();

    void call(uint16_t interrupt);
};

#endif // INTERRUPTHANDLER_H
