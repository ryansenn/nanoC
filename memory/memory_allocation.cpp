//
// Created by Ryan Senoune on 2025-01-15.
//

#include "memory_allocation.h"

void MemoryAllocation::visit(std::shared_ptr<Program> p) {
    for(auto s : p->decls){
        s->accept(*this);
    }
}

void MemoryAllocation::visit(std::shared_ptr<FuncDecl> f) {

    for (auto a : f->args){
        a->type->accept(*this);
    }


    // accounting for return address
    int offset = 8;

    for (auto it = f->args.rbegin();it != f->args.rend(); ++it){
        offset += (*it)->type->size;
        it->get()->offset = offset;
    }

    f->block->accept(*this);

}

void MemoryAllocation::visit(std::shared_ptr<Block> b) {
    b->offset = scopes.back()->offset;
    scopes.push_back(b);

    for (auto s : b->stmts){
        s->accept(*this);
    }

    scopes.pop_back();
}

void MemoryAllocation::visit(std::shared_ptr<Return> f) {

}

void MemoryAllocation::visit(std::shared_ptr<Primary> p){

}

void MemoryAllocation::visit(std::shared_ptr<Call> c){

}

void MemoryAllocation::visit(std::shared_ptr<Binary> b){

}

void MemoryAllocation::visit(std::shared_ptr<VarDecl> v){

}

void MemoryAllocation::visit(std::shared_ptr<If> f) {

}

void MemoryAllocation::visit(std::shared_ptr<While>){

}
void MemoryAllocation::visit(std::shared_ptr<Break>){

}
void MemoryAllocation::visit(std::shared_ptr<Continue>){

}
void MemoryAllocation::visit(std::shared_ptr<Subscript>){

}
void MemoryAllocation::visit(std::shared_ptr<Member>){

}

void MemoryAllocation::visit(std::shared_ptr<Unary>){

}
void MemoryAllocation::visit(std::shared_ptr<TypeCast>){

}
void MemoryAllocation::visit(std::shared_ptr<Type> t){
    // size of type
    switch (t->token->token_type) {
        case TT::INT:
            t->size = 8;
            break;
        case TT::VOID:
            t->size = 0;
            break;
        case TT::CHAR:
            t->size = 8;
            break;
        case TT::STRUCT:
            t->size = std::dynamic_pointer_cast<StructDecl>(t->symbol->decl)->size;
            break;
        default:
            break;
    }

    if (t->pointerCount > 0){
        t->size = 8;
    }
}
void MemoryAllocation::visit(std::shared_ptr<FunProto>){

}
void MemoryAllocation::visit(std::shared_ptr<StructDecl>){

}