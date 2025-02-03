//
// Created by Ryan Senoune on 2025-02-01.
//

#include "code_gen.h"


void CodeGen::generate(){

    if (curr()->opcode == "global"){
        file << "section .data" << std::endl;

        while (curr()->opcode == "global"){
            file << curr()->label << ": resq " << std::to_string(std::stoi(curr()->value)/8) << std::endl;
        }

    }

    file << "section .text" << std::endl;


}