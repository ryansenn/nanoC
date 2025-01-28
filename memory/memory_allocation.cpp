//
// Created by Ryan Senoune on 2025-01-15.
//

#include "memory_allocation.h"


int MemoryAllocation::align(int offset, int alignment) {
    return offset + ((alignment - (offset % alignment)) % alignment);
}

void MemoryAllocation::visit(std::shared_ptr<StructDecl> s){
    int alignment;
    int maxAlignment = 0;
    int offset = 0;

    for (auto v : s->varDecls){
        v->accept(*this);
        alignment = v->type->size;
        maxAlignment = std::max(maxAlignment, alignment);

        offset = align(offset, alignment);
        v->offset = offset;
        offset += v->type->size;
    }

    offset = align(offset, maxAlignment);
    s->size = offset;
}


void MemoryAllocation::visit(std::shared_ptr<FuncDecl> f) {

    for (auto a : f->args){
        a->type->accept(*this);
    }


    // accounting for return address and pushed rbp
    int offset = 16;

    for (auto it = f->args.rbegin();it != f->args.rend(); ++it){
        it->get()->offset = offset;
        offset += (*it)->type->size;
        std::cout << f->name + " " << it->get()->name + " " + std::to_string(it->get()->offset) << std::endl;
    }


    //f->arg_offset = align(offset - 8, 8);
    f->arg_offset = offset - 16;

    f->block->accept(*this);


}

void MemoryAllocation::visit(std::shared_ptr<Block> b) {
    //scopes.back()->offset = align(scopes.back()->offset, 8);

    b->offset = scopes.back()->offset;

    scopes.push_back(b);

    for (auto s : b->stmts){
        s->accept(*this);
    }

    //scopes.back()->offset = align(scopes.back()->offset, 8);

    scopes.pop_back();
}

void MemoryAllocation::visit(std::shared_ptr<VarDecl> v){
    v->type->accept(*this);
    if (v->is_local){
        scopes.back()->offset += v->type->size;
        v->offset = -scopes.back()->offset;
    }
}

void MemoryAllocation::visit(std::shared_ptr<Return> f) {

}

void MemoryAllocation::visit(std::shared_ptr<Primary> p){

}

void MemoryAllocation::visit(std::shared_ptr<Call> c){

}

void MemoryAllocation::visit(std::shared_ptr<Binary> b){

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

// TODO Change type size by using subset of registers
// TODO or write directly in stack instead of using push instruction
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

void MemoryAllocation::visit(std::shared_ptr<Program> p) {
    for(auto s : p->decls){
        s->accept(*this);
    }
}