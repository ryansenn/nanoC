//
// Created by Ryan Senoune on 2024-05-07.
//
#include <string>
#include <unordered_map>
#include <iostream>

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

enum class TokenType {
    IDENTIFIER, ASSIGN, LBRA, RBRA, LPAR, RPAR, LSBR, RSBR, SC, COMMA,
    INT, VOID, CHAR, IF, ELSE, WHILE, RETURN, STRUCT, SIZEOF, CONTINUE, BREAK,
    INCLUDE, CHAR_LITERAL, STRING_LITERAL, INT_LITERAL, LOGAND, LOGOR,
    EQ, NE, LT, GT, LE, GE, PLUS, MINUS, ASTERISK, DIV, REM, AND, OR, DOT,
    END_OF_FILE, INVALID, COMMENT
};

using TT = TokenType;

extern std::unordered_map<TokenType, std::string> tokenNames;

extern std::unordered_map<std::string, TokenType> tokenMap;

std::string getTokenName(TokenType tokenType);

struct Token{
    Token(TokenType token_type, const std::string& value, int line, int column) : token_type(token_type), value(value), line(line), column(column) {}
    TokenType token_type;
    std::string value;
    int line;
    int column;
};

std::string getTokenPos(Token token);

std::ostream& operator<<(std::ostream& os, const TokenType& t);

#endif //COMPILER_TOKEN_H
