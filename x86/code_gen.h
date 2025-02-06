//
// Created by Ryan Senoune on 2025-02-01.
//

#ifndef COMPILER_CODE_GEN_H
#define COMPILER_CODE_GEN_H

#include <fstream>
#include "../ir/ir.h"

class CodeGen {
public:

    std::ofstream file;
    std::vector<std::shared_ptr<Instruction>> instructions;
    int index = 0;
    std::unordered_map<std::string, int> reg_alloc;


    CodeGen(const std::string &filename,
            std::vector<std::shared_ptr<Instruction>> &&instructions,
            std::unordered_map<std::string, int> &&reg_alloc) :
            file(filename), instructions(instructions), reg_alloc(reg_alloc) {}

    std::shared_ptr<Instruction> curr() {
        return instructions[index];
    }

    void emit(std::string s) {
        file << s << std::endl;
    }

    void generate();
    void generate(std::shared_ptr<Instruction> i);
    void generate(std::shared_ptr<BasicInstruction> i);
    void generate(std::shared_ptr<GlobalVariable> i);
    void generate(std::shared_ptr<BranchInstruction> i);
    void generate(std::shared_ptr<Label> i);


};
#endif //COMPILER_CODE_GEN_H
