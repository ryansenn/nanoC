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
    std::string value;
    Register(std::string name) : name(name) {}
};

class AsmContext {
private:
    std::ofstream file;
    std::vector<std::shared_ptr<Register>> registers;
    std::unordered_map<std::string, std::shared_ptr<Register>> reg_map;
    int registerCount = 0;
    std::shared_ptr<Register> NO_REGISTER;

    void initRegistersMap() {
        for (const auto& reg : registers) {
            reg_map[reg->name] = reg;
        }
    }

public:
    AsmContext(const std::string& filename) :
            file(filename),
            NO_REGISTER(std::make_shared<Register>("NO REGISTER")) {

        registers = {
                std::make_shared<Register>("r10"),
                std::make_shared<Register>("r11"),
                std::make_shared<Register>("r12"),
                std::make_shared<Register>("r13"),
                std::make_shared<Register>("r9"),
                std::make_shared<Register>("r8"),
                std::make_shared<Register>("rcx"),
                std::make_shared<Register>("rdx"),
                std::make_shared<Register>("rsi"),
                std::make_shared<Register>("rdi")
        };
        initRegistersMap();
    }

    std::shared_ptr<Register> getRegister() {
        return registers[registerCount++ % registers.size()];
    }

    void freeRegister(std::shared_ptr<Register>) {}

    std::ofstream& getFile() { return file; }

    const std::shared_ptr<Register>& getNullRegister() const {
        return NO_REGISTER;
    }

    ~AsmContext() {
        if (file.is_open()) {
            file.close();
        }
    }
};

#endif // ASM_CONTEXT_H