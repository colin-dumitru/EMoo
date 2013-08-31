#include "cpu.h"
#include "interpreter.h"
#include "machine.h"

Cpu::Cpu() {
    interpreter = new Interpreter();
    decoder = new Decoder(&machine.ram);

    registerTable[AX] = &ax;
    registerTable[CX] = &cx;
    registerTable[DX] = &dx;
    registerTable[BX] = &bx;
    registerTable[SP] = &sp;
    registerTable[BP] = &bp;
    registerTable[SI] = &sp;
    registerTable[DI] = &di;
    registerTable[ZR] = &zero;
}

Cpu::~Cpu() {
    delete interpreter;
    delete decoder;
}
