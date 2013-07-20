#include "ram.h"

Ram::Ram()
{
}

void Ram::loadFromFile(char *filename, uint8_t address) {
    FILE* file = fopen(filename, "rb");
    size_t result = 0;

    while((result = fread(buffer, sizeof(u_int8_t), 0x100, file)) == 0x100) {
    }

    fclose(file);
}
