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

    std::shared_ptr<Register> copy(int size){
        return std::make_shared<Register>(name, name_d, name_w, name_b, size, isVirtual, isMemoryOperand);
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

    static std::shared_ptr<Register> get_physical_register(std::string name, int size, bool mem){
        for (auto r : registers){
            if (r->name == name){
                auto res = r->copy(size);
                res->isMemoryOperand = mem;
                return res;
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
    std::string opcode;
    virtual ~Instruction() = default;
};

class BasicInstruction : public Instruction {
public:
    std::string value;

    BasicInstruction(std::string opcode_, std::vector<std::shared_ptr<Register>> regs) {
        registers = regs;
        opcode = opcode_;
    }

    BasicInstruction(std::string opcode_, std::vector<std::shared_ptr<Register>> regs, std::string value) :
        value(value) {
        registers = regs;
        opcode = opcode_;
    }

    BasicInstruction(std::string opcode_) {
            opcode = opcode_;
        }


};

class BranchInstruction : public Instruction {
public:
    std::string label;

    BranchInstruction(std::string opcode_, std::string label)
            : label(label) {
        opcode=opcode_;
    }

    BranchInstruction(std::string opcode_,
                      std::vector<std::shared_ptr<Register>> regs){
        registers = regs;
        opcode = opcode_;
    }

};

class Label : public Instruction {
public:
    std::string label;
    bool funcDecl;

    Label(std::string label, bool funcDecl)
            : label(std::move(label)), funcDecl(funcDecl) {
        opcode = "LABEL";
    }

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