//
// Created by Ryan Senoune on 2025-01-15.
//

#ifndef COMPILER_MEMORY_H
#define COMPILER_MEMORY_H

#include "../parser/ast.h"


class MemoryAllocation : public Visitor<void> {
    std::vector<std::shared_ptr<Block>> scopes = {std::make_shared<Block>()};

    int align(int offset, int alignment);

    void visit(std::shared_ptr<Program>) override;
    void visit(std::shared_ptr<FuncDecl>) override;
    void visit(std::shared_ptr<Block>) override;
    void visit(std::shared_ptr<Return>) override;
    void visit(std::shared_ptr<If>) override;
    void visit(std::shared_ptr<While>) override;
    void visit(std::shared_ptr<Break>) override;
    void visit(std::shared_ptr<Continue>) override;
    void visit(std::shared_ptr<VarDecl>) override;
    void visit(std::shared_ptr<Subscript>) override;
    void visit(std::shared_ptr<Member>) override;
    void visit(std::shared_ptr<Call>) override;
    void visit(std::shared_ptr<Primary>) override;
    void visit(std::shared_ptr<Unary>) override;
    void visit(std::shared_ptr<TypeCast>) override;
    void visit(std::shared_ptr<Binary>) override;
    void visit(std::shared_ptr<Type>) override;
    void visit(std::shared_ptr<FunProto>) override;
    void visit(std::shared_ptr<StructDecl>) override;
};


#endif //COMPILER_MEMORY_H
