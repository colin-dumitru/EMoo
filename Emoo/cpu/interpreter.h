#ifndef INTERPRETER_H
#define INTERPRETER_H

class Interpreter {
private:
    Cpu* cpu;
    InstructionCache* cache;
public:
    Interpreter(Cpu* cpu);
    ~Interpreter();

    void interpret(uint32_t address);
};
#endif // INTERPRETER_H
