//
// Created by Ryan Senoune on 2025-01-17.
//

#include "addr_gen.h"


std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Program> p) {
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<FuncDecl> f) {
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Block> b) {
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Primary> p){

    if (p->token->token_type == TT::IDENTIFIER){
        std::shared_ptr<Register> r = asmContext->getRegister();

        int offset = std::dynamic_pointer_cast<VarDecl>(p->symbol->decl)->offset;

        asmContext->emit("lea " + r->name + ", " + address(offset));

        return r;
    }

    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Member> m){
    std::shared_ptr<Register> r = m->structure->accept(*this);
    int offset = std::dynamic_pointer_cast<VarDecl>( m->symbol->decl)->offset;
    asmContext->emit("add " + r->name + ", " + std::to_string(offset));
    return r;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Unary> u){

    if (u->op->token_type == TT::ASTERISK && u->expr1->type->token->token_type == TT::STRUCT) {
        return u->expr1->accept(*this);
    }

    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Call> c){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Binary> b){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<If> f) {
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<While> w){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Subscript>){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<TypeCast>){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Return> f) {
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Break>){
    return NO_REGISTER;
}
std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Continue>){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<FunProto>){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<VarDecl> v){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<StructDecl>){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Type>){
    return NO_REGISTER;
}