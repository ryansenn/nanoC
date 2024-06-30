//
// Created by Ryan Senoune on 2024-05-07.
//

#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include "token.h"

class Lexer {
    std::string source_code;
    int index = 0;
    public:
    Lexer(const std::string& source_code);
    std::shared_ptr<Token> nextToken();
    bool reachedEnd();
    private:
    char peak();
    char consume();
    int line = 1;
    int column = 1;
};


#endif //COMPILER_LEXER_H
