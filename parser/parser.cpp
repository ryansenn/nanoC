//
// Created by Ryan Senoune on 2024-05-14.
//

#include "parser.h"

Parser::Parser(Lexer &lexer):lexer(lexer) {}

std::shared_ptr<Program> Parser::program(){
    while (accept(TT::INCLUDE)){
        include();
    }

    std::vector<std::shared_ptr<Decl>> decls;

    while (!accept(TT::END_OF_FILE)){
        decls.push_back(decl());
    }

    return std::make_shared<Program>(std::move(decls));
}

void Parser::include(){
    consume(TT::INCLUDE, "Expected #include directive");
}

std::shared_ptr<Token> Parser::consume(TT expected, const std::string& message){
    if (accept(expected)){
        std::shared_ptr<Token> token = std::move(buffer[0]);
        buffer.pop_front();
        return token;
    }

    throw parsing_exception(message, peek(0));
}

std::shared_ptr<Token> Parser::consume(std::vector<TT> expected, const std::string& message){
    if (accept(expected)){
        std::shared_ptr<Token> token = std::move(buffer[0]);
        buffer.pop_front();
        return token;
    }

    throw parsing_exception(message, peek(0));
}

bool Parser::accept(std::vector<TT> expected, int i){
    for (auto t : expected){
        if (accept(t,i)){
            return true;
        }
    }
    return false;
}

bool Parser::accept(std::vector<TT> expected){
    for (auto t : expected){
        if (accept(t)){
            return true;
        }
    }
    return false;
}

bool Parser::accept(TT expected){
    return peek(0)->token_type == expected;
}

bool Parser::accept(TT expected, int i){
    return peek(i)->token_type == expected;
}

std::shared_ptr<Token> Parser::peek(int i) {
    for(int j=0;j<i - int(buffer.size()) + 1; j++){
        buffer.push_back(lexer.nextToken());
    }

    return buffer[i];
}
