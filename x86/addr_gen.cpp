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

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Block> f) {
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Return> f) {
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Primary> p){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Call> c){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Binary> b){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<VarDecl> v){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<If> f) {
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<While>){
    return NO_REGISTER;
}
std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Break>){
    return NO_REGISTER;
}
std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Continue>){
    return NO_REGISTER;
}
std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Subscript>){
    return NO_REGISTER;
}
std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Member>){
    return NO_REGISTER;
}

std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Unary>){
    return NO_REGISTER;
}
std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<TypeCast>){
    return NO_REGISTER;
}
std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<Type>){
    return NO_REGISTER;
}
std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<FunProto>){
    return NO_REGISTER;
}
std::shared_ptr<Register> AddrGen::visit(std::shared_ptr<StructDecl>) {
    return NO_REGISTER;
}