#ifndef COMMON_H
#define COMMON_H

#include "config.h"
#include "stdint.h"
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
#define ERR(...) fprintf(stderr, "[ERR] "); fprintf (stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define ERR(...)
#endif

#ifdef DEBUG
#define DEB(x) (x);
#else
#define DEB(x)
#endif

#define LOW(op) *(uint8_t*)(&(op))
#define HIGH(op) *(((uint8_t*)(&(op))) + 1)
#define WORD(op) (uint16_t*)(op)
#define SIGNED8(op) (int8_t)(op)
#define SIGNED16(op) (int16_t)(op)

#define REPEAT8(x) x;x;x;x;x;x;x;x;
#define REPEAT32(x) REPEAT8(x) REPEAT8(x) REPEAT8(x) REPEAT8(x)
#endif
