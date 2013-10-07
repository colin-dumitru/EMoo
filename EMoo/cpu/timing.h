#ifndef TIMING_H
#define TIMING_H

#include <sys/time.h>
#include "io/vga.h"
#include "common.h"

MACHINE_AWARE

class Timing
{
private:
    timeval currentTime;

    void refreshTime();

public:
    uint64_t tick;

    Timing();

    void update();
};

inline void Timing::refreshTime() {
    gettimeofday (&currentTime, NULL);
    tick = (uint64_t) currentTime.tv_sec * (uint64_t) 1000000 + (uint64_t) currentTime.tv_usec;
}

#endif // TIMING_H
