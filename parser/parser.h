//
// Created by Ryan Senoune on 2024-05-14.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "../lexer/lexer.h"
#include "ast.h"
#include "parsing_exception.h"
#include <deque>
#include <vector>
#include <fstream>

class Parser{

public:
    Parser(Lexer& lexer);

    std::shared_ptr<Type> type();
    std::shared_ptr<Expr> access(std::shared_ptr<Expr> prev);
    std::shared_ptr<Expr> funccall();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> sum();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> equality();
    std::shared_ptr<Expr> logor();
    std::shared_ptr<Expr> logand();
    std::shared_ptr<Expr> assignment();
    std::shared_ptr<Expr> expr();
    std::shared_ptr<Stmt> stmt();
    void array(std::shared_ptr<Type>& t);
    std::vector<std::shared_ptr<VarDecl>> args();
    std::shared_ptr<Decl> decl();
    std::shared_ptr<VarDecl> vardecl();
    std::shared_ptr<StructDecl> structdecl();
    std::shared_ptr<Decl> funcdecl(std::shared_ptr<Type> t, std::string& name);
    std::shared_ptr<Block> block();
    std::vector<std::shared_ptr<Decl>> include();
    std::shared_ptr<Program> program();
    std::shared_ptr<Token> consume(TT expected, const std::string& message);
    std::shared_ptr<Token> consume(std::vector<TT> expected, const std::string& message);
    bool accept(TT expected);
    bool accept(TT expected, int i);
    bool accept(std::vector<TT> expected);
    bool accept(std::vector<TT> expected, int i);
    std::shared_ptr<Token> peek(int amount);


private:
    Lexer& lexer;
    std::deque<std::shared_ptr<Token>> buffer;
};

#endif //COMPILER_PARSER_H
