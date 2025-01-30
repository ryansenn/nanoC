//
// Created by Ryan Senoune on 2025-01-17.
//

#ifndef ASM_CONTEXT_H
#define ASM_CONTEXT_H

#include "../parser/ast.h"
#include <fstream>

class Register {
public:
    std::string name;
    std::string name_d;
    std::string name_w;
    std::string name_b;
    std::string value;

    Register(std::string name, std::string name_d, std::string name_w, std::string name_b)
            : name(name), name_d(name_d), name_w(name_w), name_b(name_b) {}

    std::string addr(){
        return "[" + name  + "]";
    }
};


class AsmContext {
public:
    std::ofstream file;
    std::vector<std::shared_ptr<Register>> registers = {
            std::make_shared<Register>("r10", "r10d", "r10w", "r10b"),
            std::make_shared<Register>("r11", "r11d", "r11w", "r11b"),
            std::make_shared<Register>("r12", "r12d", "r12w", "r12b"),
            std::make_shared<Register>("r13", "r13d", "r13w", "r13b"),
            std::make_shared<Register>("r9", "r9d", "r9w", "r9b"),
            std::make_shared<Register>("r8", "r8d", "r8w", "r8b"),
            std::make_shared<Register>("rcx", "ecx", "cx", "cl"),
            std::make_shared<Register>("rsi", "esi", "si", "sil"),
            std::make_shared<Register>("rdi", "edi", "di", "dil"),
            std::make_shared<Register>("rdx", "edx", "dx", "dl"),
            std::make_shared<Register>("rax", "eax", "ax", "al")
    };

    std::unordered_map<std::string, std::shared_ptr<Register>> reg_map;
    std::shared_ptr<Register> NO_REGISTER;

    int MAX_REGISTER = 9;
    int curr_register = 0;
    int curr_label = 0;

    std::shared_ptr<Register> getRegister() {
        if (curr_register >= MAX_REGISTER){
            spill();
        }
        return registers[curr_register++ % MAX_REGISTER];
    }

    void freeRegister(std::shared_ptr<Register> r) {
        if (curr_register >= MAX_REGISTER){

        }
    }

    std::string getLabel(std::string s){
        return s + std::to_string(curr_label++);
    }

    void emit(std::string s) {
        file << s << std::endl;
    }

    void initRegistersMap() {
        for (const auto& reg : registers) {
            reg_map[reg->name] = reg;
        }
    }

    AsmContext(const std::string& filename) :
            file(filename),
            NO_REGISTER(std::make_shared<Register>("NO REGISTER", "", "", "")) {

        initRegistersMap();
    }

    ~AsmContext() {
        if (file.is_open()) {
            file.close();
        }
    }
};

#endif // ASM_CONTEXT_H