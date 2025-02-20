//
// Created by Ryan Senoune on 2025-01-29.
//

#ifndef COMPILER_CFG_GEN_H
#define COMPILER_CFG_GEN_H

#include "ir.h"


class BasicBlock {
public:
    static int count;
    int id;
    std::vector<std::shared_ptr<Instruction>> instructions;
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



#endif //COMPILER_CFG_GEN_H