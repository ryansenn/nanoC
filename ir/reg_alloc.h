//
// Created by Ryan Senoune on 2025-02-02.
//

#ifndef COMPILER_NAIVEREGALLOC_H
#define COMPILER_NAIVEREGALLOC_H

#include "ir.h"

/*
 * This is an extremely inefficient (but fully working) register allocator
 * All virtual registers are assigned a memory slot in the .bss section (`reg_alloc`).
 * Loads the memory slot into a physical register (r10 or 11) and writes back after execution
 */
std::unordered_map<std::string, std::string> global_reg_alloc(std::vector<std::shared_ptr<Instruction>>& instructions) {
    std::vector<std::shared_ptr<Instruction>> n_instructions;
    std::unordered_map<std::string, std::string> reg_to_mem;
    std::vector<std::string> pool = {"r10", "r11"};
    int offset = 0;



    for (auto inst : instructions) {
        std::vector<std::shared_ptr<Instruction>> write_back;

        for (int i=0;i<inst->registers.size();i++){
            auto reg = inst->registers[i];
            if (reg->isVirtual){
                if (inst->opcode == "lea" && i == 1){
                    continue;
                }
                if (reg_to_mem.find(reg->name) == reg_to_mem.end()){
                    reg_to_mem[reg->name] = "[rel reg_alloc + " + std::to_string(offset) + "]";
                    offset += 8;
                }
                std::shared_ptr<Register> physical = Register::get_physical_register(pool[i%2],reg->size, false);
                std::vector<std::shared_ptr<Register>> load = {physical,reg};
                std::vector<std::shared_ptr<Register>> write = {reg,physical};

                n_instructions.push_back(std::make_shared<BasicInstruction>("mov", load));
                write_back.push_back(std::make_shared<BasicInstruction>("mov",write));

                inst->registers[i] = Register::get_physical_register(pool[i%2],reg->size, reg->isMemoryOperand);

            }
        }
        n_instructions.push_back(inst);
        for (auto w : write_back){
            n_instructions.push_back(w);
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
