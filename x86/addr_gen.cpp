//
// Created by Ryan Senoune on 2025-01-17.
//

#include "addr_gen.h"


Address AddrGen::visit(std::shared_ptr<Program> p) {
    return Address("", 0);
}

Address AddrGen::visit(std::shared_ptr<FuncDecl> f) {
    return Address("", 0);
}

Address AddrGen::visit(std::shared_ptr<Block> f) {
    return Address("", 0);
}

Address AddrGen::visit(std::shared_ptr<Return> f) {
    return Address("", 0);
}

Address AddrGen::visit(std::shared_ptr<Primary> p){

    std::shared_ptr<VarDecl> v = std::dynamic_pointer_cast<VarDecl>(p->symbol->decl);
    return Address("rbp", v->offset);

}

Address AddrGen::visit(std::shared_ptr<Member> m){
    Address a = m->structure->accept(*this);
    std::cout << a.str() << std::endl;
    a.offset += std::dynamic_pointer_cast<VarDecl>(m->symbol->decl)->offset;
    std::cout << a.str() << std::endl;
    return a;
}

Address AddrGen::visit(std::shared_ptr<Call> c){
    return Address("", 0);
}

Address AddrGen::visit(std::shared_ptr<Binary> b){
    return Address("", 0);
}

Address AddrGen::visit(std::shared_ptr<VarDecl> v){
    return Address("rbp", v->offset);
}

Address AddrGen::visit(std::shared_ptr<If> f) {
    return Address("", 0);
}

Address AddrGen::visit(std::shared_ptr<While>){
    return Address("", 0);
}
Address AddrGen::visit(std::shared_ptr<Break>){
    return Address("", 0);
}
Address AddrGen::visit(std::shared_ptr<Continue>){
    return Address("", 0);
}
Address AddrGen::visit(std::shared_ptr<Subscript>){
    return Address("", 0);
}

Address AddrGen::visit(std::shared_ptr<Unary>){
    return Address("", 0);
}
Address AddrGen::visit(std::shared_ptr<TypeCast>){
    return Address("", 0);
}
Address AddrGen::visit(std::shared_ptr<Type>){
    return Address("", 0);
}
Address AddrGen::visit(std::shared_ptr<FunProto>){
    return Address("", 0);
}
Address AddrGen::visit(std::shared_ptr<StructDecl>) {
    return Address("", 0);
}