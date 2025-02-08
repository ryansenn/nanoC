//
// Created by Ryan Senoune on 2025-02-02.
//

#ifndef COMPILER_NAIVEREGALLOC_H
#define COMPILER_NAIVEREGALLOC_H

#include "ir.h"

/*
 * This is an extremely inefficient (but fully working) register allocator
 * All virtual registers are assigned a memory slot in the .bss section (`reg_alloc`).
 * On every access, the value is loaded from memory into a physical register and store back after execution
 */
std::unordered_map<std::string, std::string> global_reg_alloc(std::vector<std::shared_ptr<Instruction>>& instructions) {
    std::vector<std::shared_ptr<Instruction>> n_instructions;
    std::unordered_map<std::string, std::string> reg_to_mem;
    int offset = 0;

    for (const auto& inst : instructions) {
        for (const auto& reg : inst->registers) {
            if (reg->isVirtual){
                if (reg_to_mem.find(reg->name) == reg_to_mem.end()) {
                    reg_to_mem[reg->name] = "[rel reg_alloc + " + std::to_string(offset) + "]";
                    offset += 8;
                }
            }
        }

        if (inst->registers.size() == 1 && inst->registers[0]->isVirtual){
            std::shared_ptr<Register> reg = inst->registers[0];
            std::vector<std::shared_ptr<Register>> regs = {Register::get_physical_register("r10"),reg};
            n_instructions.push_back(std::make_shared<BasicInstruction>("mov", regs));

        }

        if (inst->registers.size() == 2 && inst->registers[1]->isVirtual){
            std::shared_ptr<Register> reg = inst->registers[1];
            std::vector<std::shared_ptr<Register>> regs = {Register::get_physical_register("r11"),reg};
            n_instructions.push_back(std::make_shared<BasicInstruction>("mov", regs));
        }

        n_instructions.push_back(inst);

        if (inst->registers.size() == 1 && inst->registers[0]->isVirtual){
            std::shared_ptr<Register> reg = inst->registers[0];
            std::vector<std::shared_ptr<Register>> regs = {reg,Register::get_physical_register("r10")};
            n_instructions.back()->registers[0] = Register::get_physical_register("r10");
            n_instructions.push_back(std::make_shared<BasicInstruction>("mov", regs));
        }

        if (inst->registers.size() == 2 && inst->registers[1]->isVirtual){
            std::shared_ptr<Register> reg = inst->registers[1];
            std::vector<std::shared_ptr<Register>> regs = {reg,Register::get_physical_register("r11")};
            n_instructions.back()->registers[1] = Register::get_physical_register("r11");
            n_instructions.push_back(std::make_shared<BasicInstruction>("mov", regs));
        }
    }

    if (offset > 0) {
        std::shared_ptr<GlobalVariable> data_array = std::make_shared<GlobalVariable>("resq","reg_alloc",offset);
        n_instructions.insert(n_instructions.begin(), data_array);
    }

    instructions = std::move(n_instructions);

    return reg_to_mem;
}


#endif //COMPILER_NAIVEREGALLOC_H
