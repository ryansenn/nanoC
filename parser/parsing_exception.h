//
// Created by Ryan Senoune on 2024-05-25.
//

#ifndef COMPILER_PARSING_EXCEPTION_H
#define COMPILER_PARSING_EXCEPTION_H

#include <stdexcept>
#include <string>

class parsing_exception : public std::exception {
public:
    std::string msg;
    int line;
    int col;
    std::string full_msg;
    parsing_exception(const std::string& m, std::shared_ptr<Token> token) : msg(m), line(token->line), col(token->column){
        full_msg = "Parsing error: " + msg + " at line " + std::to_string(line) + " column " + std::to_string(col) + " found " +
                getTokenName(token->token_type);
    }

    const char* what() const noexcept override {
        return full_msg.c_str();
    }
};

#endif //COMPILER_PARSING_EXCEPTION_H
