//
// Created by Ryan Senoune on 2025-01-29.
//

#include "cfg_gen.h"

int VirtualRegister::count = 0;
int BasicBlock::count = 0;


std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Program> p) {
    for (auto d : p->decls){
        d->accept(*this);
    }

    return NO_REGISTER;
}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<FuncDecl> f) {
    curr_cfg = std::make_shared<CFG>(f->name);

    std::shared_ptr<BasicBlock> entry = std::make_shared<BasicBlock>();
    curr_cfg->entry = entry;
    curr_block = entry;

    f->block->accept(*this);

    std::shared_ptr<BasicBlock> exit = std::make_shared<BasicBlock>();
    curr_cfg->exit = exit;

    results.push_back(curr_cfg);

    return NO_REGISTER;
}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Block> b) {
    for (auto s : b->stmts){
        s->accept(*this);
    }

    return NO_REGISTER;
}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<VarDecl> v) {
    if (v->is_local){
        symbol_table[v] = getRegister();
    }

    return NO_REGISTER;
}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Primary> p) {

    std::shared_ptr<VirtualRegister> r;

    switch (p->token->token_type) {
        case TT::INT_LITERAL:
        case TT::CHAR_LITERAL:
            r = getRegister();
            emit("mov", r, p->token->value);
            break;
        case TT::IDENTIFIER: {
            r = symbol_table[std::dynamic_pointer_cast<VarDecl>(p->symbol->decl)];
            break;
        }
        default:
            break;
    }

    return r;
}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Binary> b) {

}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Return> ret) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<If> ifStmt) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<While> whileStmt) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Break> breakStmt) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Continue> continueStmt) {

}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Subscript> subscript) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Member> member) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Call> call) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Unary> unary) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<TypeCast> typeCast) {

}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Type> type) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<FunProto> funProto) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<StructDecl> structDecl) {

}

void cfg_gen::emit(std::string opcode, std::shared_ptr<VirtualRegister> r1, std::shared_ptr<VirtualRegister> r2){
    std::vector<std::shared_ptr<VirtualRegister>> r = {r1,r2};
    std::shared_ptr<Instruction> i = std::make_shared<Instruction>(opcode, r);
    curr_block->instructions.push_back(i);
}
void cfg_gen::emit(std::string opcode, std::shared_ptr<VirtualRegister> r1){
    std::vector<std::shared_ptr<VirtualRegister>> r = {r1};
    std::shared_ptr<Instruction> i = std::make_shared<Instruction>(opcode, r);
    curr_block->instructions.push_back(i);
}

void cfg_gen::emit(std::string opcode, std::shared_ptr<VirtualRegister> r1, std::string value){
    std::vector<std::shared_ptr<VirtualRegister>> r = {r1};
    std::shared_ptr<Instruction> i = std::make_shared<Instruction>(opcode, r, value);
    curr_block->instructions.push_back(i);
}

std::shared_ptr<VirtualRegister> cfg_gen::getRegister(){
    return std::make_shared<VirtualRegister>();
}
