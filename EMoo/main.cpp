#include "common.h"
#include "machine.h"
#include <unistd.h>
#include <time.h>

void runNormal() {
    machine.reset();
    machine.ram.loadFromFile(BIOS_FILE, 0xFE000);
    machine.cpu.ip.data = 0x0000;
    machine.cpu.cs.data = 0xFFFF;

    while(1) {
        machine.step();
    }
}

void runTest() {
    clock_t start;
    clock_t end;
    int instructions = 0;

    start = clock();

    machine.reset();
    machine.ram.loadFromFile(BIOS_FILE, 0xFE000);
    machine.cpu.ip.data = 0x0000;
    machine.cpu.cs.data = 0xFFFF;

    while(instructions++ < 1000000) {
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
