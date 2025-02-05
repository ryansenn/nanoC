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

class Instruction{
public:
    std::string opcode;
    std::vector<std::shared_ptr<VirtualRegister>> registers;
    std::string value;
    std::string label;

    Instruction(std::string opcode, std::vector<std::shared_ptr<VirtualRegister>> registers) :
            opcode(opcode), registers(registers) {}

    Instruction(std::string opcode, std::vector<std::shared_ptr<VirtualRegister>> registers, std::string value) :
            opcode(opcode), registers(registers), value(value) {}

    Instruction(std::string opcode) :
            opcode(opcode) {}

};

class BranchInstruction : public Instruction {
public:
    std::string label;

    BranchInstruction(std::string opcode, std::string label)
            : Instruction(opcode), label(label) {}

    BranchInstruction(std::string opcode,
                      std::vector<std::shared_ptr<VirtualRegister>> registers)
            : Instruction(opcode, registers){}
};

class Label : public Instruction {
public:
    std::string label;
    bool funcDecl;

    Label(std::string label, bool funcDecl)
            : Instruction("LABEL"), label(std::move(label)), funcDecl(funcDecl) {}

};

#endif //COMPILER_IR_H
