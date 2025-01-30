//
// Created by Ryan Senoune on 2025-01-29.
//

#ifndef COMPILER_CFG_GEN_H
#define COMPILER_CFG_GEN_H


#include "../parser/ast.h"

class CFGNode {
public:
    int id;
    std::vector<std::shared_ptr<CFGNode>> successors;
    CFGNode(int i) : id(i) {}
};

class BasicBlock {
public:
    int id;
    std::vector<std::shared_ptr<CFGNode>> nodes;
    BasicBlock(int i) : id(i) {}
};

class cfg_gen : public Visitor<std::shared_ptr<BasicBlock>> {
public:

    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Program> program) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<FuncDecl> func) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Block> block) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Return> ret) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<If> ifStmt) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<While> whileStmt) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Break> breakStmt) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Continue> continueStmt) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<VarDecl> varDecl) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Subscript> subscript) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Member> member) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Call> call) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Primary> primary) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Unary> unary) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<TypeCast> typeCast) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Binary> binary) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<Type> type) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<FunProto> funProto) override {
        return nullptr;
    }
    std::shared_ptr<BasicBlock> visit(std::shared_ptr<StructDecl> structDecl) override {
        return nullptr;
    }
};



#endif //COMPILER_CFG_GEN_H
