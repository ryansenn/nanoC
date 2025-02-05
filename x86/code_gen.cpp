//
// Created by Ryan Senoune on 2025-02-01.
//

#include "code_gen.h"


void CodeGen::generate(std::shared_ptr<BasicInstruction> i){

}
void CodeGen::generate(std::shared_ptr<GlobalVariable> i){

}
void CodeGen::generate(std::shared_ptr<BranchInstruction> i){

}
void CodeGen::generate(std::shared_ptr<Label> i){

}

void CodeGen::generate(std::shared_ptr<Instruction> i) {
    if (auto basic = std::dynamic_pointer_cast<BasicInstruction>(i)) {
        generate(basic);
    }
    else if (auto global = std::dynamic_pointer_cast<GlobalVariable>(i)) {
        generate(global);
    }
    else if (auto branch = std::dynamic_pointer_cast<BranchInstruction>(i)) {
        generate(branch);
    }
    else if (auto label = std::dynamic_pointer_cast<Label>(i)) {
        generate(label);
    }
}

void CodeGen::generate(){

    if (std::dynamic_pointer_cast<GlobalVariable>(curr()) ){
        emit("section .data");

        while (std::dynamic_pointer_cast<GlobalVariable>(curr())){
            generate(curr());
            index++;
        }
    }

    emit("section .text");
    emit("global start");

    while (index < instructions.size()) {
        generate(curr());
        index++;
    }

    emit("start:");
    emit("call main");
    emit("mov rdi, rax");
    emit("mov rax, 0x2000001");
    emit("syscall");

}

