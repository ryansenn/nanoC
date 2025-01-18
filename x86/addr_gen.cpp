//
// Created by Ryan Senoune on 2025-01-17.
//

#include "addr_gen.h"


std::string AddrGen::visit(std::shared_ptr<Program> p) {
    return "";
}

std::string AddrGen::visit(std::shared_ptr<FuncDecl> f) {
    return "";
}

std::string AddrGen::visit(std::shared_ptr<Block> f) {
    return "";
}

std::string AddrGen::visit(std::shared_ptr<Return> f) {
    return "";
}

std::string AddrGen::visit(std::shared_ptr<Primary> p){

    std::shared_ptr<VarDecl> v = std::dynamic_pointer_cast<VarDecl>(p->symbol->decl);
    return v->getAddress();
}

std::string AddrGen::visit(std::shared_ptr<Call> c){
    return "";
}

std::string AddrGen::visit(std::shared_ptr<Binary> b){
    return "";
}

std::string AddrGen::visit(std::shared_ptr<VarDecl> v){
    return "";
}

std::string AddrGen::visit(std::shared_ptr<If> f) {
    return "";
}

std::string AddrGen::visit(std::shared_ptr<While>){
    return "";
}
std::string AddrGen::visit(std::shared_ptr<Break>){
    return "";
}
std::string AddrGen::visit(std::shared_ptr<Continue>){
    return "";
}
std::string AddrGen::visit(std::shared_ptr<Subscript>){
    return "";
}
std::string AddrGen::visit(std::shared_ptr<Member>){
    return "";
}

std::string AddrGen::visit(std::shared_ptr<Unary>){
    return "";
}
std::string AddrGen::visit(std::shared_ptr<TypeCast>){
    return "";
}
std::string AddrGen::visit(std::shared_ptr<Type>){
    return "";
}
std::string AddrGen::visit(std::shared_ptr<FunProto>){
    return "";
}
std::string AddrGen::visit(std::shared_ptr<StructDecl>) {
    return "";
}