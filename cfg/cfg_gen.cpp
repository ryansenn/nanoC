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
}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<FuncDecl> f) {
    curr_cfg = std::make_shared<CFG>(f->name);
    f->block->accept(*this);
    results.push_back(curr_cfg);
}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Block> b) {
    for (auto s : b->stmts){
        s->accept(*this);
    }
}

std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Primary> p) {

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
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<VarDecl> varDecl) {

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
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Binary> binary) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<Type> type) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<FunProto> funProto) {

}
std::shared_ptr<VirtualRegister> cfg_gen::visit(std::shared_ptr<StructDecl> structDecl) {

}