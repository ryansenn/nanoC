//
// Created by Ryan Senoune on 2025-02-02.
//

#ifndef COMPILER_NAIVEREGALLOC_H
#define COMPILER_NAIVEREGALLOC_H

#include "ir.h"

/*
 * This is an extremely inefficient (but fully working) register allocator
 * All virtual registers are assigned a memory slot in the .bss section (`reg_alloc`).
 * If an instruction uses two virtual registers (invalid in x86, must have one physical register),
 * Then one value is loaded from memory into a physical register and written back after execution
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

        if (inst->registers.size() == 2 && inst->registers[0]->isVirtual && inst->registers[1]->isVirtual){
            std::shared_ptr<Register> reg = inst->registers[0];
            std::vector<std::shared_ptr<Register>> regs = {Register::get_physical_register("r11", reg->size),reg};
            n_instructions.push_back(std::make_shared<BasicInstruction>("mov", regs));
        }

        n_instructions.push_back(inst);

        if (inst->registers.size() == 2 && inst->registers[0]->isVirtual && inst->registers[1]->isVirtual){
            std::shared_ptr<Register> reg = inst->registers[0];
            std::shared_ptr<BasicInstruction> old = std::dynamic_pointer_cast<BasicInstruction>(n_instructions.back());
            std::vector<std::shared_ptr<Register>> old_regs = {Register::get_physical_register("r11", reg->size), old->registers[1]};
            n_instructions.back() = std::make_shared<BasicInstruction>(old->opcode,old_regs);

            std::vector<std::shared_ptr<Register>> regs = {reg,Register::get_physical_register("r11", reg->size)};
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
