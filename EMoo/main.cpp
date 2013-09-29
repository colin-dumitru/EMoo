#include "common.h"
#include "machine.h"
#include <unistd.h>
#include <time.h>


void reset() {
    machine.reset();

    machine.ram.loadFromFile(BIOS_FILE, 0xFE000);
    machine.ram.loadFromFile(VROM_FILE, 0xC0000);

    machine.cpu.ip.data = 0x0000;
    machine.cpu.cs.data = 0xFFFF;
}

void runNormal() {
    reset();

    while(1) {
        machine.step();
    }
}

void runTest() {
    clock_t start;
    clock_t end;
    int instructions = 0;

    uint8_t x = 0xFF;

    printf("%x\n", x << 4);

    start = clock();

    reset();

    while(instructions++ < 1000000) {
        if(instructions == 481219 ) {
            int a = 0;
        }
        machine.step();
    }

    end = clock();

    printf("diff: %f ms\n", 1000.0 * (end-start) / CLOCKS_PER_SEC);
    printf("start: %lu\n", start);
    printf("end: %lu\n", end);

    bool temp = 0x8000;
    printf("%d\n", temp);
}

int main() {
    runTest();
    //runNormal();
}
