#ifndef COMMON_H
#define COMMON_H

#include "config.h"
#include <stdio.h>

#define MACHINE_AWARE \
class Machine; \
extern Machine machine;

#ifdef DEBUG
#define LOG(...) printf("[LOG] "); fprintf (stdout, __VA_ARGS__); printf("\n")
#else
#define LOG(...)
#endif

#ifdef DEBUG
#define ERR(...) printf("[ERR] "); fprintf (stderr, __VA_ARGS__); printf("\n")
#else
#define ERR(...)
#endif

#define LOW(op) *(uint8_t*)(&(op))
#define HIGH(op) *(((uint8_t*)(&(op))) + 1)

#endif
