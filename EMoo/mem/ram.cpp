#include "ram.h"

Ram::Ram()
{
}

void Ram::loadFromFile(const char *filename, uint32_t address) {
    FILE* file = fopen(filename, "rb");
    size_t result = 0;

    while((result = fread(buffer + address, sizeof(u_int8_t), 0x100, file)) == 0x100) {
    }

    fclose(file);
}

void Ram::write(uint32_t address, uint8_t *source, uint32_t length) {
    memcpy(buffer + address, source, length);
}
