#include "interpreter.h"
#include "cpu.h"

Interpreter::Interpreter(Cpu* cpu) : decoder(cpu->decoder)
{
}

Interpreter::~Interpreter()
{
}
