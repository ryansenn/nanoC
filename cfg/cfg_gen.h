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

class cfg_gen : public Visitor<void> {
public:

    std::vector<std::shared_ptr<CFG>> results;

    std::shared_ptr<CFG> curr_cfg;
    std::shared_ptr<BasicBlock> curr_block;

    void visit(std::shared_ptr<Program> p) override {
        for (auto d : p->decls){
            d->accept(*this);
        }
    }

    void visit(std::shared_ptr<FuncDecl> f) override {
        curr_cfg = std::make_shared<CFG>(f->name);
        f->block->accept(*this);
        results.push_back(curr_cfg);
    }

    void visit(std::shared_ptr<Block> b) override {
        for (auto s : b->stmts){
            s->accept(*this);
        }
    }
    void visit(std::shared_ptr<Return> ret) override {

    }
    void visit(std::shared_ptr<If> ifStmt) override {

    }
    void visit(std::shared_ptr<While> whileStmt) override {

    }
    void visit(std::shared_ptr<Break> breakStmt) override {

    }
    void visit(std::shared_ptr<Continue> continueStmt) override {

    }
    void visit(std::shared_ptr<VarDecl> varDecl) override {

    }
    void visit(std::shared_ptr<Subscript> subscript) override {

    }
    void visit(std::shared_ptr<Member> member) override {

    }
    void visit(std::shared_ptr<Call> call) override {

    }
    void visit(std::shared_ptr<Primary> primary) override {

    }
    void visit(std::shared_ptr<Unary> unary) override {

    }
    void visit(std::shared_ptr<TypeCast> typeCast) override {

    }
    void visit(std::shared_ptr<Binary> binary) override {

    }
    void visit(std::shared_ptr<Type> type) override {

    }
    void visit(std::shared_ptr<FunProto> funProto) override {

    }
    void visit(std::shared_ptr<StructDecl> structDecl) override {

    }
};



#endif //COMPILER_CFG_GEN_H
