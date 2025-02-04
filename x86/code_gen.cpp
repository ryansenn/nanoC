//
// Created by Ryan Senoune on 2025-02-01.
//

#include "code_gen.h"


void CodeGen::generate(){

    if (curr()->opcode == "global"){
        file << "section .data" << std::endl;

        while (curr()->opcode == "global"){
            file << curr()->label << ": resq " << std::to_string(std::stoi(curr()->value)/8) << std::endl;
            index++;
        }
    }

    file << "section .text" << std::endl;
    file << "global main" << std::endl;
    file << "main:" << std::endl;


    file << "    push rbp" << std::endl;
    file << "    mov rbp, rsp" << std::endl;


    while (index < instructions.size()) {

        index++;
    }


    file << "    mov rsp, rbp" << std::endl;
    file << "    pop rbp" << std::endl;
    file << "    ret" << std::endl;


}