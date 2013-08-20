#include "cpu.h"

Cpu::Cpu() {
    interpreter = new Interpreter(this);
    decoder = new Decoder(this);
}

Cpu::~Cpu() {
    delete interpreter;
    delete decoder;
}

Decoder::Decoder(Cpu *cpu) : cpu(cpu) {
}

void Decoder::decode(uint32_t address, Instruction *instruction) {

}

Interpreter::Interpreter(Cpu *cpu) : cpu(cpu) {
    cache = new InstructionCache(this->cpu);
}

Interpreter::~Interpreter() {
    delete cache;
}

void Interpreter::interpret(uint32_t address) {

}

InstructionCache::InstructionCache(Cpu* cpu) : cpu(cpu){
}

void InstructionCache::executeNew(uint32_t address) {
    cacheHandlers[address] = &InstructionCache::executeFromCache;
    cpu->decoder->decode(address, &instructionCache[address]);

}

void InstructionCache::executeFromCache(uint32_t address) {

}
