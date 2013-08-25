#include "cpu.h"
#include "machine.h"

Cpu::Cpu() {
    interpreter = new Interpreter(decoder);
    decoder = new Decoder(&machine.ram);
}

Cpu::~Cpu() {
    delete interpreter;
    delete decoder;
}
