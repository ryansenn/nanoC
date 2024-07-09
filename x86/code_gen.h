//
// Created by Ryan Senoune on 2024-07-08.
//

#ifndef COMPILER_CODE_GEN_H
#define COMPILER_CODE_GEN_H

#include "fstream"
#include "../parser/ast.h"

class Register{

};

class VirtualRegister : public Register {

};

class CodeGen : public Visitor<std::shared_ptr<Register>> {
public:
    std::ofstream file;

    CodeGen(std::string name) : file(name) {}

    std::shared_ptr<Register> visit(std::shared_ptr<Program>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<FuncDecl>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Block>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Return>) override;
};


#endif //COMPILER_CODE_GEN_H
