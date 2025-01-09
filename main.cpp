#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "parser/parser.h"
#include "semantic/name_analysis.h"
#include "semantic/type_analysis.h"
#include "x86/code_gen.h"

void printTokens(Lexer& lexer){
    std::shared_ptr<Token> token = lexer.nextToken();

    while (token->token_type != TokenType::END_OF_FILE){
        if (token->value != ""){
            std::cout << tokenNames.find(token->token_type)->second << " " << token->value << std::endl;
        }
        else{
            std::cout << tokenNames.find(token->token_type)->second << std::endl;
        }
        token = lexer.nextToken();
    }
}


int main(int argc, char *argv[]) {

    if (argc < 2){
        std::cerr << "Incorrect Usage, correct usage is..." << std::endl;
        std::cerr << "compiler <sourcecode.c>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string content;

    if (file){
        std::stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
    }
    else{
        std::cerr << "Source code file not found" << std::endl;
        return 1;
    }

    Lexer lexer(content);

    if (argc > 2 && strcmp(argv[2],"-lexer") == 0){
        try{
            printTokens(lexer);
            return 0;
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }

    }

    Parser parser(lexer);
    std::shared_ptr<Program> program;
    try{
        program = parser.program();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (argc > 2 && strcmp(argv[2],"-ast") == 0){
        PrintVisitor p;
        program->accept(p);
        return 0;
    }

    try{
        program->addStandardLibrary();

        NameAnalysis n;
        program->accept(n);

        TypeAnalysis t;
        program->accept(t);

        CodeGen c("output.asm");
        program->accept(c);

    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }




    return 0;
}


