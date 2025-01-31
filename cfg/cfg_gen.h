//
// Created by Ryan Senoune on 2025-01-29.
//

#ifndef COMPILER_CFG_GEN_H
#define COMPILER_CFG_GEN_H


#include "../parser/ast.h"

class VirtualRegister {
public:
    static int count;
    int id;
    VirtualRegister() : id(count++) {}
};

class Instruction{
    std::string opcode;
    std::vector<std::shared_ptr<VirtualRegister>> registers;
    Instruction(std::string opcode) : opcode(opcode) {}
};

class BasicBlock {
public:
    static int count;
    int id;
    std::vector<std::shared_ptr<Instruction>> instructions;
    std::vector<std::shared_ptr<BasicBlock>> predecessors;
    std::vector<std::shared_ptr<BasicBlock>> successors;
    BasicBlock() : id(count++) {}
};

class CFG {
public:
    std::string name;
    std::shared_ptr<BasicBlock> entry;
    std::shared_ptr<BasicBlock> exit;
    CFG(std::string name) : name(name) {}
};

class cfg_gen : public Visitor<std::shared_ptr<VirtualRegister>> {
public:

    std::vector<std::shared_ptr<CFG>> results;

    std::shared_ptr<CFG> curr_cfg;
    std::shared_ptr<BasicBlock> curr_block;

    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Program> p) override {
        for (auto d : p->decls){
            d->accept(*this);
        }
    }

    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<FuncDecl> f) override {
        curr_cfg = std::make_shared<CFG>(f->name);
        f->block->accept(*this);
        results.push_back(curr_cfg);
    }

    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Block> b) override {
        for (auto s : b->stmts){
            s->accept(*this);
        }
    }

    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Primary> primary) override {

    }

    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Return> ret) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<If> ifStmt) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<While> whileStmt) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Break> breakStmt) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Continue> continueStmt) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<VarDecl> varDecl) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Subscript> subscript) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Member> member) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Call> call) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Unary> unary) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<TypeCast> typeCast) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Binary> binary) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Type> type) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<FunProto> funProto) override {

    }
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<StructDecl> structDecl) override {

    }
};



#endif //COMPILER_CFG_GEN_H
