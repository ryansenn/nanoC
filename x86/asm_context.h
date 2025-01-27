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
    int registerCount = 0;
    std::shared_ptr<Register> NO_REGISTER;
    int labelCounter = 0;

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

    std::shared_ptr<Register> getRegister() {
        return registers[registerCount++ % 9];
    }

    std::string getLabel(std::string s){
        return s + std::to_string(labelCounter++);
    }

    void freeRegister(std::shared_ptr<Register>) {}

    void emit(std::string s) {
        file << s << std::endl;
    }

    ~AsmContext() {
        if (file.is_open()) {
            file.close();
        }
    }
};

#endif // ASM_CONTEXT_H