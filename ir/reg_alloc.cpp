//
// Created by Ryan Senoune on 2025-02-12.
//

#include "reg_alloc.h"

/*
* Naive register allocator - maps every virtual register to a stack location
* Loads to physical register and writes back to stack upon every usage
*/
std::unordered_map<std::string, std::string> RegAlloc::naive_reg_alloc(std::vector<std::shared_ptr<Instruction>>& instructions) {
    std::unordered_map<std::string, std::string> reg_to_mem;
    std::vector<std::string> func_to_offset;
    std::vector<std::string> pool = {"r10", "r11"};
    int offset = 0;

    for (int i=0;i<instructions.size();i++) {
        auto inst = instructions[i];
        if (inst->opcode == "ret") {
            func_to_offset.push_back(std::to_string(offset));
            offset = 0;
        }

        for (auto reg : inst->registers) {
            if (reg->isVirtual && reg_to_mem.find(reg->name) == reg_to_mem.end()) {
                offset += 8;
                reg_to_mem[reg->name] = "[rbp - " + std::to_string(offset) + "]";
            }
        }

        if (inst->opcode == "allocate"){
            offset += std::stoi(std::dynamic_pointer_cast<BasicInstruction>(inst)->value);
            instructions[i] = emit("lea", inst->registers[0], "[rbp - " + std::to_string(offset) + "]");
        }
    }

    int label = 0;
    for (int i=0; i<instructions.size(); i++) {
        if (auto p = std::dynamic_pointer_cast<Label>(instructions[i]); p && p->funcDecl) {
            n_instructions.push_back(instructions[i]);
            n_instructions.push_back(instructions[i+1]);
            n_instructions.push_back(instructions[i+2]);
            n_instructions.push_back(emit("sub", Register::get_physical_register("rsp"), func_to_offset[label++]));
            i += 3;
        }

        auto inst = instructions[i];

        std::vector<std::shared_ptr<Instruction>> write_back;

        for (int i=0;i<inst->registers.size();i++){
            auto reg = inst->registers[i];
            if (reg->isVirtual){
                if (inst->opcode == "lea" && i == 1){
                    continue;
                }

                auto physical = Register::get_physical_register(pool[i%2], reg->size, reg->isMemoryOperand);
                n_instructions.push_back(emit("mov", Register::get_physical_register(pool[i%2]), reg->copy(8)));
                inst->registers[i] = physical;

                if (i == 0){
                    write_back.push_back(emit("mov", reg->copy(8), Register::get_physical_register(pool[i%2])));
                }
            }
        }
        n_instructions.push_back(inst);

        for (auto w : write_back){
            n_instructions.push_back(w);
        }

    }

    instructions = std::move(n_instructions);

    return reg_to_mem;
}

std::shared_ptr<Instruction> RegAlloc::emit(std::string opcode, std::shared_ptr<Register> r1, std::shared_ptr<Register> r2){
    std::vector<std::shared_ptr<Register>> r = {r1,r2};
    std::shared_ptr<Instruction> i = std::make_shared<BasicInstruction>(opcode, r);
    return i;
}

std::shared_ptr<Instruction> RegAlloc::emit(std::string opcode, std::shared_ptr<Register> r1, std::string value){
    std::vector<std::shared_ptr<Register>> r = {r1};
    std::shared_ptr<Instruction> i = std::make_shared<BasicInstruction>(opcode, r, value);
    return i;
}