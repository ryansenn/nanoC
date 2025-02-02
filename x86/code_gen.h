//
// Created by Ryan Senoune on 2025-02-01.
//

#ifndef COMPILER_CODE_GEN_H
#define COMPILER_CODE_GEN_H

#include <fstream>
#include "../ir/instruction_gen.h"

class CodeGen {
public:

    std::ofstream file;
    std::vector<std::shared_ptr<Instruction>>& instructions;


    CodeGen(const std::string& filename, std::vector<std::shared_ptr<Instruction>> instructions) :
            file(filename), instructions(instructions) {}

    void generate(){

    }

};


#endif //COMPILER_CODE_GEN_H
