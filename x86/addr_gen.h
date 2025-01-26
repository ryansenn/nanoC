//
// Created by Ryan Senoune on 2025-01-17.
//

#ifndef COMPILER_ADDR_GEN_H
#define COMPILER_ADDR_GEN_H

#include "asm_context.h"
#include "../parser/ast.h"
#include "fstream"



class AddrGen : public Visitor<Address>{
public:
    std::shared_ptr<AsmContext> asmContext;
    AddrGen(std::shared_ptr<AsmContext> asmContext) : asmContext(asmContext) {}


    Address visit(std::shared_ptr<Program>) override;
    Address visit(std::shared_ptr<FuncDecl>) override;
    Address visit(std::shared_ptr<Block>) override;
    Address visit(std::shared_ptr<Return>) override;
    Address visit(std::shared_ptr<If>) override;
    Address visit(std::shared_ptr<While>) override;
    Address visit(std::shared_ptr<Break>) override;
    Address visit(std::shared_ptr<Continue>) override;
    Address visit(std::shared_ptr<VarDecl>) override;
    Address visit(std::shared_ptr<Subscript>) override;
    Address visit(std::shared_ptr<Member>) override;
    Address visit(std::shared_ptr<Call>) override;
    Address visit(std::shared_ptr<Primary>) override;
    Address visit(std::shared_ptr<Unary>) override;
    Address visit(std::shared_ptr<TypeCast>) override;
    Address visit(std::shared_ptr<Binary>) override;
    Address visit(std::shared_ptr<Type>) override;
    Address visit(std::shared_ptr<FunProto>) override;
    Address visit(std::shared_ptr<StructDecl>) override;
};


#endif //COMPILER_ADDR_GEN_H
