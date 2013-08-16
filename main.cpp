#include "common.h"
#include "machine.h"

void runNormal() {

}

void runTest() {
    machine.ram.loadFromFile(TEST_FILE, 0x000F0000);
}

int main() {

}
