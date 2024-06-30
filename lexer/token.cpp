//
// Created by Ryan Senoune on 2024-05-09.
//

#include "token.h"

std::unordered_map<TokenType, std::string> tokenNames = {
{TokenType::IDENTIFIER, "Identifier"}, {TokenType::ASSIGN, "="},
{TokenType::LBRA, "Left Brace"}, {TokenType::RBRA, "Right Brace"},
{TokenType::LPAR, "Left Parenthesis"}, {TokenType::RPAR, "Right Parenthesis"},
{TokenType::LSBR, "Left Square Bracket"}, {TokenType::RSBR, "Right Square Bracket"},
{TokenType::SC, "Semicolon"}, {TokenType::COMMA, "Comma"},
{TokenType::INT, "Integer"}, {TokenType::VOID, "Void"},
{TokenType::CHAR, "Character"}, {TokenType::IF, "If"},
{TokenType::ELSE, "Else"}, {TokenType::WHILE, "While"},
{TokenType::RETURN, "Return"}, {TokenType::STRUCT, "Structure"},
{TokenType::SIZEOF, "Sizeof"}, {TokenType::CONTINUE, "Continue"},
{TokenType::BREAK, "Break"}, {TokenType::INCLUDE, "Include"},
{TokenType::CHAR_LITERAL, "Character Literal"}, {TokenType::STRING_LITERAL, "String Literal"},
{TokenType::INT_LITERAL, "Integer Literal"}, {TokenType::LOGAND, "&&"},
{TokenType::LOGOR, "||"}, {TokenType::EQ, "=="},
{TokenType::NE, "!="}, {TokenType::LT, "<"},
{TokenType::GT, ">"}, {TokenType::LE, "<="},
{TokenType::GE, ">="}, {TokenType::PLUS, "+"},
{TokenType::MINUS, "-"}, {TokenType::ASTERISK, "*"},
{TokenType::DIV, "/"}, {TokenType::REM, "%"},
{TokenType::AND, "&"}, {TokenType::DOT, "."},
{TokenType::END_OF_FILE, "End of File"}, {TokenType::INVALID, "Invalid"},
{TokenType::COMMENT, "Comment"}
};

std::unordered_map<std::string, TokenType> tokenMap = {
        {"=", TokenType::ASSIGN},
        {"{", TokenType::LBRA}, {"}", TokenType::RBRA},
        {"(", TokenType::LPAR}, {")", TokenType::RPAR},
        {"[", TokenType::LSBR}, {"]", TokenType::RSBR},
        {";", TokenType::SC}, {",", TokenType::COMMA},
        {"int", TokenType::INT}, {"void", TokenType::VOID}, {"char", TokenType::CHAR},
        {"if", TokenType::IF}, {"else", TokenType::ELSE}, {"while", TokenType::WHILE},
        {"return", TokenType::RETURN}, {"struct", TokenType::STRUCT}, {"sizeof", TokenType::SIZEOF},
        {"continue", TokenType::CONTINUE}, {"break", TokenType::BREAK},
        {"#include", TokenType::INCLUDE}, {"&&", TokenType::LOGAND}, {"||", TokenType::LOGOR},
        {"==", TokenType::EQ}, {"!=", TokenType::NE}, {"<", TokenType::LT},
        {">", TokenType::GT}, {"<=", TokenType::LE}, {">=", TokenType::GE},
        {"+", TokenType::PLUS}, {"-", TokenType::MINUS}, {"*", TokenType::ASTERISK},
        {"/", TokenType::DIV}, {"%", TokenType::REM}, {"&", TokenType::AND},
        {".", TokenType::DOT}
};

std::string getTokenName(TokenType tokenType){
    return tokenNames.find(tokenType)->second;
}

std::string getTokenPos(Token& token){
    return " line " + std::to_string(token.line) + " column " + std::to_string(token.column);
}

std::ostream& operator<<(std::ostream& os, const TokenType& t) {
    os << getTokenName(t);
    return os;
}