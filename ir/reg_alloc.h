//
// Created by Ryan Senoune on 2025-02-02.
//

#ifndef COMPILER_NAIVEREGALLOC_H
#define COMPILER_NAIVEREGALLOC_H

#include "ir.h"

class RegAlloc{
public:
    std::vector<std::shared_ptr<Instruction>> n_instructions;

    std::unordered_map<std::string, std::string> naive_reg_alloc(std::vector<std::shared_ptr<Instruction>>& instructions);
    std::shared_ptr<Instruction> emit(std::string opcode, std::shared_ptr<Register> r1, std::shared_ptr<Register> r2);
    std::shared_ptr<Instruction> emit(std::string opcode, std::shared_ptr<Register> r1, std::string value);

};



#endif //COMPILER_NAIVEREGALLOC_H
