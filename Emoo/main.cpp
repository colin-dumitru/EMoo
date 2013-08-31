#include "common.h"
#include "machine.h"
#include <unistd.h>

void runNormal() {

}

void runTest() {
    machine.ram.loadFromFile(TEST_FILE, 0x000F0000);
}

int main() {
    uint16_t x = 0x1234;

    printf("%x\n", x);

    //((uint8_t*)&x)[0] = 0x00;

    printf("%x\n", ((uint8_t*)&x)[0]);

    while(true) {
        machine.step();
        usleep(1);
    }
}
