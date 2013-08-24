#ifndef DECODER_H
#define DECODER_H

class Decoder {
private:
    Cpu* cpu;


public:
    Decoder(Cpu* cpu);

    void decode(uint32_t address, Instruction* instruction);
};

#endif // DECODER_H
