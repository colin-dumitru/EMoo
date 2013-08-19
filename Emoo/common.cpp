#include "common.h"

void log(char* message) {
#ifdef DEBUG
    printf("[DEBUG] %s", message);
#endif
}
