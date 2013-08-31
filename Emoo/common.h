#ifndef COMMON_H
#define COMMON_H

#include "config.h"
#include <stdio.h>

#define MACHINE_AWARE \
class Machine; \
extern Machine machine;

#ifdef DEBUG
#define LOG(message) printf("[LOG] %s", message)
#else
#define LOG(message)
#endif

#ifdef DEBUG
#define ERR(message) printf("[ERR] %s", message)
#else
#define ERR(message)
#endif

#define LOW(op) ((uint8_t*)&(#op))[0]
#define HIGH(op) ((uint8_t*)&(#op))[1]

#endif
