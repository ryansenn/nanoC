//
// Created by Ryan Senoune on 2025-01-17.
//

#ifndef COMPILER_ADDR_GEN_H
#define COMPILER_ADDR_GEN_H

#include "asm_context.h"
#include "fstream"

class AddrGen : public Visitor<std::shared_ptr<Register>>{

    std::ofstream file;

    AddrGen(std::ofstream file) : file(file) {}


    std::shared_ptr<Register> visit(std::shared_ptr<Program>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<FuncDecl>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Block>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Return>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<If>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<While>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Break>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Continue>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<VarDecl>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Subscript>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Member>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Call>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Primary>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Unary>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<TypeCast>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Binary>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Type>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<FunProto>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<StructDecl>) override;
};


#endif //COMPILER_ADDR_GEN_H
