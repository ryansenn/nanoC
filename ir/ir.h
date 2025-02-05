//
// Created by Ryan Senoune on 2025-02-02.
//

#ifndef COMPILER_IR_H
#define COMPILER_IR_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>

class VirtualRegister {
public:
    static int count;
    int id;
    VirtualRegister() : id(count++) {}
};


class Instruction {
public:
    virtual ~Instruction() = default;  // Virtual destructor for polymorphism
};

class BasicInstruction : public Instruction {
public:
    std::string opcode;
    std::vector<std::shared_ptr<VirtualRegister>> registers;
    std::string value;

    BasicInstruction(std::string opcode, std::vector<std::shared_ptr<VirtualRegister>> registers) :
            opcode(opcode), registers(registers) {}

    BasicInstruction(std::string opcode, std::vector<std::shared_ptr<VirtualRegister>> registers, std::string value) :
            opcode(opcode), registers(registers), value(value) {}

    BasicInstruction(std::string opcode) :
            opcode(opcode) {}
};

class BranchInstruction : public Instruction {
public:
    std::string opcode;
    std::string label;
    std::vector<std::shared_ptr<VirtualRegister>> registers;

    BranchInstruction(std::string opcode, std::string label)
            : opcode(opcode), label(label) {}

    BranchInstruction(std::string opcode,
                      std::vector<std::shared_ptr<VirtualRegister>> registers)
            : opcode(opcode), registers(registers) {}
};

class Label : public Instruction {
public:
    std::string opcode;
    std::string label;
    bool funcDecl;

    Label(std::string label, bool funcDecl)
            : opcode("LABEL"), label(std::move(label)), funcDecl(funcDecl) {}
};

class GlobalVariable : public Instruction {
public:
    std::string label;
    std::string directive;
    std::string value;
    int size;

    // Constructor for uninitialized variables (e.g., resq 4)
    GlobalVariable(std::string directive, std::string label, int size)
            : directive(std::move(directive)), label(std::move(label)), value(""), size(size) {}
};

#endif //COMPILER_IR_H
