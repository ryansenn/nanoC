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
    std::unordered_map<std::string, std::string> reg_alloc;



    CodeGen(const std::string &filename,
            std::vector<std::shared_ptr<Instruction>> &&instructions,
            std::unordered_map<std::string, std::string> &&reg_alloc) :
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

    std::string get_reg(std::shared_ptr<Register> r);

    const std::unordered_map<int, std::string> size_specifier = {
            {1, "byte"},
            {2, "word"},
            {4, "dword"},
            {8, "qword"}
    };

    std::string get_size_specifier(int size){
            auto it = size_specifier.find(size);
            return (it != size_specifier.end()) ? it->second : "unknown size";
        }

};
#endif //COMPILER_CODE_GEN_H
