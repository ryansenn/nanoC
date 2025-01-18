//
// Created by Ryan Senoune on 2025-01-17.
//

#ifndef COMPILER_ADDR_GEN_H
#define COMPILER_ADDR_GEN_H

#include "asm_context.h"
#include "fstream"

class AddrGen : public Visitor<std::string>{
public:
    std::shared_ptr<AsmContext> asmContext;
    std::shared_ptr<Register> NO_REGISTER = asmContext->NO_REGISTER;
    AddrGen(std::shared_ptr<AsmContext> asmContext) : asmContext(asmContext) {}


    std::string visit(std::shared_ptr<Program>) override;
    std::string visit(std::shared_ptr<FuncDecl>) override;
    std::string visit(std::shared_ptr<Block>) override;
    std::string visit(std::shared_ptr<Return>) override;
    std::string visit(std::shared_ptr<If>) override;
    std::string visit(std::shared_ptr<While>) override;
    std::string visit(std::shared_ptr<Break>) override;
    std::string visit(std::shared_ptr<Continue>) override;
    std::string visit(std::shared_ptr<VarDecl>) override;
    std::string visit(std::shared_ptr<Subscript>) override;
    std::string visit(std::shared_ptr<Member>) override;
    std::string visit(std::shared_ptr<Call>) override;
    std::string visit(std::shared_ptr<Primary>) override;
    std::string visit(std::shared_ptr<Unary>) override;
    std::string visit(std::shared_ptr<TypeCast>) override;
    std::string visit(std::shared_ptr<Binary>) override;
    std::string visit(std::shared_ptr<Type>) override;
    std::string visit(std::shared_ptr<FunProto>) override;
    std::string visit(std::shared_ptr<StructDecl>) override;
};


#endif //COMPILER_ADDR_GEN_H
