#include "cpu.h"
#include "machine.h"

Cpu::Cpu() {
    interpreter = new Interpreter(this);
    decoder = new Decoder(&machine.ram);
}

Cpu::~Cpu() {
    delete interpreter;
    delete decoder;
}
