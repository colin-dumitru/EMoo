#include "common.h"
#include "machine.h"
#include <unistd.h>

void runNormal() {

}

void runTest() {
    machine.ram.loadFromFile(TEST_FILE, 0x000F0000);
}

int main() {
    while(true) {
        machine.step();
        usleep(1);
    }
}
