//
// Created by Ryan Senoune on 2025-02-02.
//

#ifndef COMPILER_NAIVEREGALLOC_H
#define COMPILER_NAIVEREGALLOC_H

#include "ir.h"

std::unordered_map<std::string, std::string> naive_reg_alloc(std::vector<std::shared_ptr<Instruction>>& instructions) {

    std::unordered_map<std::string, std::string> reg_to_mem;
    int offset = 0;

    for (const auto& inst : instructions) {
        for (const auto& reg : inst->registers) {
            if (reg->isVirtual){
                if (reg && reg_to_mem.find(reg->name) == reg_to_mem.end()) {
                    reg_to_mem[reg->name] = "qword [rel reg_alloc + " + std::to_string(offset) + "]";
                    offset += 8;
                }
            }
        }
    }

    if (offset > 0) {
        std::shared_ptr<GlobalVariable> data_array = std::make_shared<GlobalVariable>("resq","reg_alloc",offset);
        instructions.insert(instructions.begin(), data_array);
    }

    return reg_to_mem;
}


#endif //COMPILER_NAIVEREGALLOC_H
