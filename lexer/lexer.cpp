#include "lexer.h"
#include <iostream>
#include <unordered_set>

std::unordered_set<char> singleCharToken = {'{','}','(',')','[',']',';',',','%',' ','.','+','-','*'};

Lexer::Lexer(const std::string& source_code) : source_code(source_code){}


std::shared_ptr<Token> Lexer::nextToken() {

    while (!reachedEnd() && (peak() == ' ' || peak() == '\n')) {
        consume();
    }

    if (reachedEnd()) {
        return std::make_shared<Token>(TokenType::END_OF_FILE, "", line, column);
    }

    if (peak() == '/') {
        consume();

        if (!reachedEnd() && peak() == '*') {
            consume();

            while (!reachedEnd()) {
                if (consume() == '*' && !reachedEnd() && peak() == '/') {
                    consume();
                    return nextToken();
                }
            }
        } else if (!reachedEnd() && peak() == '/') {
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

    if (singleCharToken.find(peak()) != singleCharToken.end()) {
        return std::make_shared<Token>(tokenMap.find(std::string(1, consume()))->second, "", line, column);
    }

    if (peak() == '=') {
        consume();
        if (!reachedEnd() && peak() == '=') {
            consume();
            return std::make_shared<Token>(TokenType::EQ, "", line, column);
        }
        return std::make_shared<Token>(TokenType::ASSIGN, "", line, column);
    }

    if (peak() == '&') {
        consume();
        if (!reachedEnd() && peak() == '&') {
            consume();
            return std::make_shared<Token>(TokenType::LOGAND, "", line, column);
        }
        return std::make_shared<Token>(TokenType::AND, "", line, column);
    }

    if (peak() == '|') {
        consume();
        if (!reachedEnd() && peak() == '|') {
            consume();
            return std::make_shared<Token>(TokenType::LOGOR, "", line, column);
        }

        return std::make_shared<Token>(TokenType::OR, "", line, column);
    }

    if (peak() == '!') {
        consume();
        if (!reachedEnd() && peak() == '=') {
            consume();
            return std::make_shared<Token>(TokenType::NE, "", line, column);
        }

        return std::make_shared<Token>(TokenType::NOT, "", line, column);
    }

    if (peak() == '<') {
        consume();
        if (!reachedEnd() && peak() == '=') {
            consume();
            return std::make_shared<Token>(TokenType::LE, "", line, column);
        }
        return std::make_shared<Token>(TokenType::LT, "", line, column);
    }

    if (peak() == '>') {
        consume();
        if (!reachedEnd() && peak() == '=') {
            consume();
            return std::make_shared<Token>(TokenType::GE, "", line, column);
        }
        return std::make_shared<Token>(TokenType::GT, "", line, column);
    }

    if (isalpha(peak()) || peak() == '_') {
        std::string word = "";

        while (!reachedEnd() && (isalnum(peak()) || peak() == '_')) {
            word += consume();
        }

        if (tokenMap.find(word) != tokenMap.end()) {
            return std::make_shared<Token>(tokenMap.find(word)->second, "", line, column);
        }

        return std::make_shared<Token>(TokenType::IDENTIFIER, word, line, column);
    }

    if (isdigit(peak())) {
        std::string word = "";

        while (!reachedEnd() && isdigit(peak())) {
            word += consume();
        }

        return std::make_shared<Token>(TokenType::INT_LITERAL, word, line, column);
    }

    if (peak() == '"') {
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

        return std::make_shared<Token>(TokenType::INVALID, "", line, column);
    }

    if (peak() == '\'') {
        std::string word = "";
        consume();

        if (!reachedEnd()) {
            char c = consume();

            if (c == '\\' && !reachedEnd()) {
                if (consume() == '\'') {
                    return std::make_shared<Token>(TokenType::CHAR_LITERAL, std::string(1, c), line, column);
                }
            }
        }

        return std::make_shared<Token>(TokenType::INVALID, "", line, column);
    }

    if (peak() == '#') {
        consume();

        while (!reachedEnd() && peak() == ' ') {
            consume();
        }
        std::string word = "";

        while (!reachedEnd() && peak() != ' ') {
            word += consume();
        }

        if (word == "include") {

            while (!reachedEnd() && peak() == ' ') {
                consume();
            }

            if (reachedEnd() || (peak() != '"' && peak() != '<')) {
                return std::make_shared<Token>(TokenType::INVALID, "", line, column);
            }

            char end = '"';

            if (consume() == '<') {
                end = '>';
            }

            word = "";

            while (!reachedEnd()) {
                if (peak() == end) {
                    consume();
                    return std::make_shared<Token>(TokenType::INCLUDE, word, line, column);
                }
                word += consume();
            }

        }
        return std::make_shared<Token>(TokenType::INVALID, "", line, column);
    }

    return std::make_shared<Token>(TokenType::INVALID, "", line, column);
}


bool Lexer::reachedEnd(){
    return index >= source_code.size();
}

char Lexer::peak(){
    if (!reachedEnd()){
        return source_code[index];
    }
    std::cerr << "Error: trying to peak when end of source code has been reached" << std::endl;
    return ' ';
}

char Lexer::consume(){
    if (peak() == '\n'){
        line++;
        column = 1;
    }
    else{
        column++;
    }
    return source_code[index++];
}