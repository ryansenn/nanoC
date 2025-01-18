//
// Created by Ryan Senoune on 2024-07-08.
//

#include "code_gen.h"

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Program> p) {
    asmContext->emit("section .text");
    asmContext->emit("global start");
    for (const auto d : p->decls){
        d->accept(*this);
    }
    asmContext->emit("start:");
    asmContext->emit("call main");
    asmContext->emit("mov rdi, rax");
    asmContext->emit("mov rax, 0x2000001");
    asmContext->emit("syscall");

    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<FuncDecl> f) {
    if (f->name == "emit_asm"){
        return NO_REGISTER;
    }

    asmContext->emit(f->name + ":");
    asmContext->emit("push rbp");
    asmContext->emit("mov rbp, rsp");

    f->block->accept(*this);

    asmContext->emit("mov rsp, rbp");
    asmContext->emit("pop rbp");
    asmContext->emit("ret");
    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Block> b) {

    asmContext->emit("sub rsp, " + std::to_string(b->offset));

    for (auto s : b->stmts){
        s->accept(*this);
    }

    asmContext->emit("add rsp, " + std::to_string(b->offset));

    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Return> f) {
    if (f->expr.has_value()){
        std::shared_ptr<Register> r = f->expr->get()->accept(*this);
        asmContext->emit("mov rax, " + r->name);
        asmContext->freeRegister(r);
    }

    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Primary> p){
    std::shared_ptr<Register> r = asmContext->getRegister();

    switch (p->token->token_type) {
        case TT::INT_LITERAL:
        case TT::CHAR_LITERAL:
            asmContext->emit("mov " + r->name + ", " + p->token->value);
            break;
        case TT::IDENTIFIER: {
            std::shared_ptr<VarDecl> v = std::dynamic_pointer_cast<VarDecl>(p->symbol->decl);
            asmContext->emit("mov " + r->name + ", " + v->getAddress());
            break;
        }
        default:
            break;
    }

    return r;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Call> c){
    std::shared_ptr<Register> r = NO_REGISTER;

    if (c->identifier->value == "emit_asm"){
        std::string instruction = std::dynamic_pointer_cast<Primary>(c->args[0])->token->value;
        asmContext->emit(instruction);
        return r;
    }

    std::shared_ptr<FuncDecl> f = std::dynamic_pointer_cast<FuncDecl>(c->symbol->decl);

    if (f->type->token->token_type != TT::VOID){
        r = asmContext->reg_map["rax"];
    }

    for (std::shared_ptr<Expr> e : c->args){
        asmContext->emit("push " + e->accept(*this)->name);
    }

    asmContext->emit("call " + c->identifier->value);
    asmContext->emit("add rsp, " + std::to_string(f->arg_offset));

    return r;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Binary> b){


    if (b->op->token_type == TT::ASSIGN){
        std::string a1 = b->expr1->accept(*addrGen);
        std::shared_ptr<Register> r2 = b->expr2->accept(*this);
        asmContext->emit("mov " + a1 + ", " + r2->name);
        return r2;
    }

    std::shared_ptr<Register> r1 = b->expr1->accept(*this);
    std::shared_ptr<Register> r2 = b->expr2->accept(*this);

    std::shared_ptr<Register> r = asmContext->getRegister();

    switch (b->op->token_type) {
        case TT::PLUS:
            asmContext->emit("mov " + r->name + ", " + r1->name);
            asmContext->emit("add " + r->name + ", " + r2->name);
            break;
        case TT::MINUS:
            asmContext->emit("mov " + r->name + ", " + r1->name);
            asmContext->emit("sub " + r->name + ", " + r2->name);
            break;
        case TT::ASTERISK:
            asmContext->emit("mov " + r->name + ", " + r1->name);
            asmContext->emit("imul " + r->name + ", " + r2->name);
            break;
        case TT::DIV:
            break;
        case TT::REM:
            break;
        case TT::LE:
            break;
        case TT::LT:
            break;
        case TT::GE:
            break;
        case TT::GT:
            break;
        case TT::EQ:
            break;
        case TT::NE:
            break;
        case TT::LOGOR:
            break;
        case TT::LOGAND:
            break;
        default:
            break;
    }

    asmContext->freeRegister(r1);
    asmContext->freeRegister(r2);

    return r;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<VarDecl> v){
    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<If> f) {
    return NULL;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<While>){
    return NULL;
}
std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Break>){
    return NULL;
}
std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Continue>){
    return NULL;
}
std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Subscript>){
    return NULL;
}
std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Member>){
    return NULL;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Unary>){
    return NULL;
}
std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<TypeCast>){
    return NULL;
}
std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Type>){
    return NULL;
}
std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<FunProto>){
    return NULL;
}
std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<StructDecl>){
    return NULL;
}