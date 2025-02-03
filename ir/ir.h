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

#endif //COMPILER_IR_H
