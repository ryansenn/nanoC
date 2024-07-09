//
// Created by Ryan Senoune on 2024-07-08.
//

#include "code_gen.h"

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Program> p) {

    file << "section .text" << std::endl;
    file << "global start" << std::endl;
    file << "start:" << std::endl;
    for (auto d : p->decls){
        d->accept(*this);
    }
    file << "mov rdi, rax" << std::endl;
    file << "mov rax, 0x2000001" << std::endl;
    file << "syscall" << std::endl;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<FuncDecl> f) {
    if (f->name == "main"){
        file << "start:" << std::endl;
    }
    else{
        file << f->name << ":" << std::endl;
    }
    f->block->accept(*this);
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Block> f) {
    for (auto s : f->stmts){
        s->accept(*this);
    }
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Return> f) {

    if (f->expr.has_value()){
        file << "mov rax 2" << std::endl;
    }
    file << "ret" << std::endl;
}