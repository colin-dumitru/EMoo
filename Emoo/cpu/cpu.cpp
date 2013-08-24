#include "cpu.h"

Cpu::Cpu() {
    interpreter = new Interpreter(decoder);
    decoder = new Decoder();
}

Cpu::~Cpu() {
    delete interpreter;
    delete decoder;
}
