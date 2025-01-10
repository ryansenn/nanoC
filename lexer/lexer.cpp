#include "lexer.h"
#include <iostream>
#include <unordered_set>

std::unordered_set<char> singleCharToken = {'{','}','(',')','[',']',';',',','%',' ','.','+','-','*'};

Lexer::Lexer(const std::string& source_code) : source_code(source_code){}


std::shared_ptr<Token> Lexer::nextToken() {

    while (!reachedEnd() && (peek() == ' ' || peek() == '\n')) {
        consume();
    }

    if (reachedEnd()) {
        return std::make_shared<Token>(TokenType::END_OF_FILE, "", line, column);
    }

    if (peek() == '/') {
        consume();

        if (!reachedEnd() && peek() == '*') {
            consume();

            while (!reachedEnd()) {
                if (consume() == '*' && !reachedEnd() && peek() == '/') {
                    consume();
                    return nextToken();
                }
            }
        } else if (!reachedEnd() && peek() == '/') {
            consume();

            while (!reachedEnd()) {
                if (consume() == '\n') {
                    return nextToken();
                }
            }
        } else {
            return std::make_shared<Token>(TokenType::DIV, "", line, column);
        }
    }

    if (reachedEnd()) {
        return std::make_shared<Token>(TokenType::END_OF_FILE, "", line, column);
    }

    if (singleCharToken.find(peek()) != singleCharToken.end()) {
        return std::make_shared<Token>(tokenMap.find(std::string(1, consume()))->second, "", line, column);
    }

    if (peek() == '=') {
        consume();
        if (!reachedEnd() && peek() == '=') {
            consume();
            return std::make_shared<Token>(TokenType::EQ, "", line, column);
        }
        return std::make_shared<Token>(TokenType::ASSIGN, "", line, column);
    }

    if (peek() == '&') {
        consume();
        if (!reachedEnd() && peek() == '&') {
            consume();
            return std::make_shared<Token>(TokenType::LOGAND, "", line, column);
        }
        return std::make_shared<Token>(TokenType::AND, "", line, column);
    }

    if (peek() == '|') {
        consume();
        if (!reachedEnd() && peek() == '|') {
            consume();
            return std::make_shared<Token>(TokenType::LOGOR, "", line, column);
        }

        return std::make_shared<Token>(TokenType::OR, "", line, column);
    }

    if (peek() == '!') {
        consume();
        if (!reachedEnd() && peek() == '=') {
            consume();
            return std::make_shared<Token>(TokenType::NE, "", line, column);
        }

        return std::make_shared<Token>(TokenType::NOT, "", line, column);
    }

    if (peek() == '<') {
        consume();
        if (!reachedEnd() && peek() == '=') {
            consume();
            return std::make_shared<Token>(TokenType::LE, "", line, column);
        }
        return std::make_shared<Token>(TokenType::LT, "", line, column);
    }

    if (peek() == '>') {
        consume();
        if (!reachedEnd() && peek() == '=') {
            consume();
            return std::make_shared<Token>(TokenType::GE, "", line, column);
        }
        return std::make_shared<Token>(TokenType::GT, "", line, column);
    }

    if (isalpha(peek()) || peek() == '_') {
        std::string word = "";

        while (!reachedEnd() && (isalnum(peek()) || peek() == '_')) {
            word += consume();
        }

        if (tokenMap.find(word) != tokenMap.end()) {
            return std::make_shared<Token>(tokenMap.find(word)->second, "", line, column);
        }

        return std::make_shared<Token>(TokenType::IDENTIFIER, word, line, column);
    }

    if (isdigit(peek())) {
        std::string word = "";

        while (!reachedEnd() && isdigit(peek())) {
            word += consume();
        }

        return std::make_shared<Token>(TokenType::INT_LITERAL, word, line, column);
    }

    if (peek() == '"') {
        std::string word = "";
        consume();
        bool escape = false;

        while (!reachedEnd()) {

            char c = consume();

            if (escape) {
                escape = false;
            } else if (c == '\\') {
                escape = true;
                continue;
            } else if (c == '"') {
                return std::make_shared<Token>(TokenType::STRING_LITERAL, word, line, column);
            }

            word += c;
        }

        throw lexing_exception("Unclosed string literal", line, column);
    }

    if (peek() == '\'') {
        consume();

        if (!reachedEnd()) {

            char c;
            if (peek() == '\\') {
                consume();
                switch (peek()) {
                    case 'n':
                        consume();
                        c = '\n';
                        break;
                    case 't':
                        consume();
                        c = '\t';
                        break;
                    case 'r':
                        consume();
                        c = '\r';
                        break;
                    case '\\':
                        consume();
                        c = '\\';
                        break;
                    case '\'':
                        consume();
                        c = '\'';
                        break;
                    case '\"':
                        consume();
                        c = '\"';
                        break;
                    case '0':
                        consume();
                        c = '\0';
                        break;
                    default:
                        throw std::runtime_error("Invalid escape sequence");
                }
            } else {
                c = consume();
            }

            if (peek() != '\''){
                throw lexing_exception("Unclosed char literal", line, column);
            }

            consume();

            return std::make_shared<Token>(TokenType::CHAR_LITERAL, std::to_string(static_cast<int>(c)), line, column);

        }

        throw lexing_exception("Unclosed char literal", line, column);
    }

    if (peek() == '#') {
        consume();

        while (!reachedEnd() && peek() == ' ') {
            consume();
        }
        std::string word = "";

        while (!reachedEnd() && peek() != ' ') {
            word += consume();
        }

        if (word == "include") {

            while (!reachedEnd() && peek() == ' ') {
                consume();
            }

            if (reachedEnd() || (peek() != '"' && peek() != '<')) {
                return std::make_shared<Token>(TokenType::INVALID, "", line, column);
            }

            char end = '"';

            if (consume() == '<') {
                end = '>';
            }

            word = "";

            while (!reachedEnd()) {
                if (peek() == end) {
                    consume();
                    return std::make_shared<Token>(TokenType::INCLUDE, word, line, column);
                }
                word += consume();
            }

        }
        throw lexing_exception("Expected \"include\" after '#'", line, column);
    }

    throw lexing_exception("Expected \"include\" after '#'", line, column);
}


bool Lexer::reachedEnd(){
    return index >= source_code.size();
}

char Lexer::peek(){
    if (!reachedEnd()){
        return source_code[index];
    }
    return ' ';
}

char Lexer::consume(){
    if (peek() == '\n'){
        line++;
        column = 1;
    }
    else{
        column++;
    }
    return source_code[index++];
}