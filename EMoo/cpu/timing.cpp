#include "timing.h"
#include "machine.h"

Timing::Timing()
{
    refreshTime();
    machine.vga.resetTiming();
}

void Timing::update() {
    refreshTime();
    machine.vga.updateTiming();
}
