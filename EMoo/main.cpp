#include "common.h"
#include "machine.h"
#include <unistd.h>
#include <time.h>

void runNormal() {

}

void runTest() {
    machine.ram.loadFromFile(TEST_FILE, 0x000F0000);
}

int main() {
    clock_t start;
    clock_t end;
    int instructions = 0;

    start = clock();

    while(instructions++ < 30000000) {
        machine.step();
    }

    end = clock();

    printf("diff: %f ms\n", 1000.0 * (end-start) / CLOCKS_PER_SEC);
    printf("start: %lu\n", start);
    printf("end: %lu\n", end);

    bool temp = true;
    printf("%x\n", 1 + temp);
}
