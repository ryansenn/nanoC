//
// Created by Ryan Senoune on 2024-07-08.
//

#ifndef COMPILER_CODE_GEN_H
#define COMPILER_CODE_GEN_H

#include "fstream"
#include "../parser/ast.h"

class Register{
public:
    std::string name;
    std::string value;
    Register(std::string name):name(name){}
};

class CodeGen : public Visitor<std::shared_ptr<Register>> {
public:
    std::ofstream file;

    CodeGen(std::string name) : file(name) {
        for (const auto& reg : registers) {
            reg_map[reg->name] = reg;
        }
    }

    int registerCount = 0;

    std::shared_ptr<Register> getRegister(){
        return registers[registerCount++ % registers.size()];
    }

    void freeRegister(std::shared_ptr<Register> r){

    }

    std::string argAddress(std::shared_ptr<VarDecl> v){
        return "[rbp + " + std::to_string(v->offset) + "]";
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

    std::shared_ptr<Register> NO_REGISTER = std::make_shared<Register>("NO REGISTER");

    std::vector<std::shared_ptr<Register>> registers = {
            std::make_shared<Register>("r10"),
            std::make_shared<Register>("r11"),
            std::make_shared<Register>("r12"),
            std::make_shared<Register>("r13"),
            std::make_shared<Register>("r9"),
            std::make_shared<Register>("r8"),
            std::make_shared<Register>("rcx"),
            std::make_shared<Register>("rdx"),
            std::make_shared<Register>("rsi"),
            std::make_shared<Register>("rdi")
    };

    std::unordered_map<std::string, std::shared_ptr<Register>> reg_map;

};


#endif //COMPILER_CODE_GEN_H
