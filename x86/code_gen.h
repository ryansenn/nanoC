//
// Created by Ryan Senoune on 2024-07-08.
//

#ifndef COMPILER_CODE_GEN_H
#define COMPILER_CODE_GEN_H

#include "fstream"
#include "../parser/ast.h"


class code_gen : public Visitor {
public:
    std::ofstream file;

    code_gen(std::string& name) : file(name) {}

    void visit(std::shared_ptr<Program>) override;
    void visit(std::shared_ptr<FuncDecl>) override;
    void visit(std::shared_ptr<Block>) override;
    void visit(std::shared_ptr<Return>) override;
};


#endif //COMPILER_CODE_GEN_H
