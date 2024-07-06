//
// Created by Ryan Senoune on 2024-05-25.
//

#ifndef COMPILER_LEXING_EXCEPTION_H
#define COMPILER_LEXING_EXCEPTION_H

#include <stdexcept>
#include <string>

class lexing_exception : public std::exception {
public:
    std::string msg;
    int line;
    int col;
    std::string full_msg;
    lexing_exception(const std::string& m, int line, int column) : msg(m), line(line), col(column){
        full_msg = "Lexing error: " + msg + " at line " + std::to_string(line) + " column " + std::to_string(col);
    }

    const char* what() const noexcept override {
        return full_msg.c_str();
    }
};

#endif //COMPILER_LEXING_EXCEPTION_H
