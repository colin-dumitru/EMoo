#ifned COMMON_H
#define COMMON_H

#include "config.h"
#include "a.out.h"
#include "machine.h"
#include <stdio.h>

Machine machine;

void log(char* message) {
#ifdef DEBUG
    printf(message);
#endif
}

#endif
