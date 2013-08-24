#ifndef INSTRUCTION_H
#define INSTRUCTION_H

class Instruction {
public:
    int8_t opcode;
    uin32_t displacement;
    uint8_t base;
    uint8_t index;
    uint8_t scale;
};


#endif // INSTRUCTION_H
