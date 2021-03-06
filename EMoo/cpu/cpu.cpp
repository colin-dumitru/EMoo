#include "cpu.h"
#include "interpreter.h"
#include "machine.h"
#include "interrupthandler.h"

Cpu::Cpu() {
    interpreter = new Interpreter();
    decoder = new Decoder(&machine.ram);
    interruptHandler = new InterruptHandler();

    registerTable[AX] = &ax;
    registerTable[CX] = &cx;
    registerTable[DX] = &dx;
    registerTable[BX] = &bx;
    registerTable[SP] = &sp;
    registerTable[BP] = &bp;
    registerTable[SI] = &si;
    registerTable[DI] = &di;
    registerTable[ZR] = &zero;

    registerAddressTable[AL] = (uint8_t*)&ax.data;
    registerAddressTable[CL] = (uint8_t*)&cx.data;
    registerAddressTable[DL] = (uint8_t*)&dx.data;
    registerAddressTable[BL] = (uint8_t*)&bx.data;
    registerAddressTable[AH] = (uint8_t*)&ax.data + sizeof(uint8_t);
    registerAddressTable[CH] = (uint8_t*)&cx.data + sizeof(uint8_t);
    registerAddressTable[DH] = (uint8_t*)&dx.data + sizeof(uint8_t);
    registerAddressTable[BH] = (uint8_t*)&bx.data + sizeof(uint8_t);

    segmentRegisterTable[ES] = &es;
    segmentRegisterTable[CS] = &cs;
    segmentRegisterTable[SS] = &ss;
    segmentRegisterTable[DS] = &ds;
}

Cpu::~Cpu() {
    delete interpreter;
    delete decoder;
}
