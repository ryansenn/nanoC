//
// Created by Ryan Senoune on 2024-05-25.
//

#ifndef COMPILER_SEMANTIC_EXCEPTION_H
#define COMPILER_SEMANTIC_EXCEPTION_H

#include <stdexcept>
#include <string>
#include "../lexer/token.h"

class semantic_exception : public std::exception {
public:
    std::string msg;
    int line;
    int col;
    std::string full_msg;
    semantic_exception(const std::string& m, std::shared_ptr<Token> token) : msg(m), line(token->line), col(token->column){
        full_msg = "Semantic error: " + msg + " at line " + std::to_string(line) + " column " + std::to_string(col);
    }

    semantic_exception(const std::string& m) : msg(m){
        full_msg = "Semantic error: " + msg;
    }

    const char* what() const noexcept override {
        return full_msg.c_str();
    }
};

#endif //COMPILER_SEMANTIC_EXCEPTION_H
