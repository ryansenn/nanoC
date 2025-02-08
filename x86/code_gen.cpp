//
// Created by Ryan Senoune on 2025-02-01.
//

#include "code_gen.h"


void CodeGen::generate(std::shared_ptr<BasicInstruction> i) {
    if (i->opcode == "emit_asm"){
        emit(i->value);
        return;
    }

    if (i->registers.size() == 1) {
        if (i->value.size()){
            emit(i->opcode + " " + get_reg(i->registers[0]) + ", " + i->value);
            return;
        }
        emit(i->opcode + " " + get_reg(i->registers[0]));
        return;
    }

    if (i->registers.size() == 2) {
        emit(i->opcode + " " + get_reg(i->registers[0]) + ", " + get_reg(i->registers[1]));
        return;
    }

    emit(i->opcode);
}
void CodeGen::generate(std::shared_ptr<GlobalVariable> i){
    emit(i->label + ": " + i->directive + " " + std::to_string(i->size));
}
void CodeGen::generate(std::shared_ptr<BranchInstruction> i){
    emit(i->opcode + " " + i->label);
}
void CodeGen::generate(std::shared_ptr<Label> i){
    if (i->funcDecl){
        emit("");
    }
    emit(i->label + ":");
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
        emit("");
    }

    emit("section .text");
    emit("global start");

    while (index < instructions.size()) {
        generate(curr());
        index++;
    }

    emit("");
    emit("start:");
    emit("call main");
    emit("mov rdi, rax");
    emit("mov rax, 0x2000001");
    emit("syscall");

}

std::string CodeGen::get_reg(std::shared_ptr<Register> r){

    std::string location;

    if (r->isVirtual){
        location = reg_alloc[r->name];
    }

    else{
        switch (r->size) {
            case 4:
                location = r->name_d;
            case 2:
                location = r->name_w;
            case 1:
                location = r->name_b;
            default:
                location = r->name;
        }
    }


    return location;
}