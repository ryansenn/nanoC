//
// Created by Ryan Senoune on 2024-07-08.
//

#ifndef COMPILER_CODE_GEN_H
#define COMPILER_CODE_GEN_H

#include "fstream"
#include "addr_gen.h"
#include "asm_context.h"



class CodeGen : public Visitor<std::shared_ptr<Register>> {
public:

    std::shared_ptr<AddrGen> addrGen;
    std::shared_ptr<AsmContext> asmContext;
    std::shared_ptr<Register> NO_REGISTER = asmContext->NO_REGISTER;

    CodeGen(std::string name) : asmContext(std::make_shared<AsmContext>(name)), addrGen(std::make_shared<AddrGen>(asmContext)){

    }

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


#endif //COMPILER_CODE_GEN_H
