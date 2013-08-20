#ifndef COMMON_H
#define COMMON_H

#include "config.h"
#include <stdio.h>

#define MACHINE_AWARE \
class Machine; \
extern Machine machine;

void log(char* message);

#endif
