//
// Created by Ryan Senoune on 2024-07-08.
//

#include "code_gen.h"

void code_gen::visit(std::shared_ptr<Program> p) {

    file << "section .text" << std::endl;
    file << "global start" << std::endl;
    for (auto d : p->decls){
        d->accept(*this);
    }
}

void code_gen::visit(std::shared_ptr<FuncDecl> f) {
    if (f->name == "main"){
        file << "start:" << std::endl;
    }
    else{
        file << f->name << ":" << std::endl;
    }
    f->block->accept(*this);
}

void code_gen::visit(std::shared_ptr<Block> f) {
    for (auto s : f->stmts){
        s->accept(*this);
    }
}

void code_gen::visit(std::shared_ptr<Return> f) {

    if (f->expr.has_value()){
        file << "mov rax " << f->expr->get() << std::endl;
    }
    file << "ret" << std::endl;
}