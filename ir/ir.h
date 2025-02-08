//
// Created by Ryan Senoune on 2025-02-02.
//

#ifndef COMPILER_IR_H
#define COMPILER_IR_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>


class Register {
public:
    std::string name;
    std::string name_d;
    std::string name_w;
    std::string name_b;
    int size = 8;
    bool isVirtual = false;
    bool isMemoryOperand = false;

    Register(std::string name, std::string name_d, std::string name_w, std::string name_b)
            : name(name), name_d(name_d), name_w(name_w), name_b(name_b) {}

    Register(std::string name, std::string name_d, std::string name_w, std::string name_b, int size, bool virt, bool mem)
            : name(name), name_d(name_d), name_w(name_w), name_b(name_b), size(size), isVirtual(virt), isMemoryOperand(mem) {}

    std::shared_ptr<Register> d(){
        return std::make_shared<Register>(name, name_d, name_w, name_b, 4, isVirtual, isMemoryOperand);
    }

    std::shared_ptr<Register> w(){
        return std::make_shared<Register>(name, name_d, name_w, name_b, 4, isVirtual, isMemoryOperand);
    }

    std::shared_ptr<Register> b(){
        return std::make_shared<Register>(name, name_d, name_w, name_b, 4, isVirtual, isMemoryOperand);
    }

    std::shared_ptr<Register> mem(){
        return std::make_shared<Register>(name, name_d, name_w, name_b, size, isVirtual, true);
    }


    static std::vector<std::shared_ptr<Register>> registers;

    static std::shared_ptr<Register> get_physical_register(std::string name){
        for (auto r : registers){
            if (r->name == name){
                return r;
            }
        }
        return nullptr;
    }

};

class VirtualRegister : public Register{
public:
    static int count;

    VirtualRegister() : Register(std::to_string(count++), "", "", "") {
        isVirtual = true;
    }

};

class CodeGen;

class Instruction {
public:
    std::vector<std::shared_ptr<Register>> registers;
    virtual ~Instruction() = default;
};

class BasicInstruction : public Instruction {
public:
    std::string opcode;
    std::string value;

    BasicInstruction(std::string opcode, std::vector<std::shared_ptr<Register>> regs) :
            opcode(opcode) {
        registers = regs;
    }

    BasicInstruction(std::string opcode, std::vector<std::shared_ptr<Register>> regs, std::string value) :
            opcode(opcode), value(value) {
        registers = regs;
    }

    BasicInstruction(std::string opcode) :
            opcode(opcode) {}

};

class BranchInstruction : public Instruction {
public:
    std::string opcode;
    std::string label;

    BranchInstruction(std::string opcode, std::string label)
            : opcode(opcode), label(label) {}

    BranchInstruction(std::string opcode,
                      std::vector<std::shared_ptr<Register>> regs)
            : opcode(opcode) {
        registers = regs;
    }

};

class Label : public Instruction {
public:
    std::string opcode;
    std::string label;
    bool funcDecl;

    Label(std::string label, bool funcDecl)
            : opcode("LABEL"), label(std::move(label)), funcDecl(funcDecl) {}

};

class GlobalVariable : public Instruction{
public:
    std::string label;
    std::string directive;
    std::string value;
    int size;

    GlobalVariable(std::string directive, std::string label, int size)
            : directive(std::move(directive)), label(std::move(label)), value(""), size(size) {}

};


#endif //COMPILER_IR_H