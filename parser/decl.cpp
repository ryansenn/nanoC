//
// Created by Ryan Senoune on 2024-06-13.
//

#include "parser.h"

std::shared_ptr<Type> Parser::type(){

    std::shared_ptr<Token> token = consume({TT::INT, TT::VOID, TT::CHAR, TT::STRUCT}, "Expected type declaration Int, Void, Char or Struct");
    std::shared_ptr<Type> t = std::make_shared<Type>(std::move(token));

    if(t->token->token_type == TT::STRUCT){
        t->name = consume(TT::IDENTIFIER, "Expected identifier after struct type")->value;
    }

    while (accept(TT::ASTERISK)){
        consume(TT::ASTERISK, "");
        t->pointerCount++;
    }

    return t;
}

void Parser::array(std::shared_ptr<Type>& t){
    while (accept(TT::LSBR)){
        consume(TT::LSBR, "");
        if (accept(TT::INT_LITERAL)){
            t->arraySize.push_back(std::stoi(consume(TT::INT_LITERAL, "")->value));
        }
        else{
            t->arraySize.push_back(-1);
        }
        consume(TT::RSBR, "Expected closing ] after [");
    }
}

std::vector<std::shared_ptr<VarDecl>> Parser::args(){
    std::vector<std::shared_ptr<VarDecl>> vardecls;

    consume(TT::LPAR, "Expected '(' in function declaration argument");

    while (!accept({TT::END_OF_FILE, TT::RPAR})){
        std::shared_ptr<Type> t = type();
        std::string name = consume(TT::IDENTIFIER, "Expected identifier in function declaration args")->value;
        array(t);
        vardecls.push_back(std::make_shared<VarDecl>(std::move(t), name));
        if (accept(TT::RPAR)){
            break;
        }
        consume(TT::COMMA, "Expected comma in function declaration args");
    }

    consume(TT::RPAR, "Expected ')' after function declaration argument");

    return vardecls;
}

std::shared_ptr<Decl> Parser::funcdecl(std::shared_ptr<Type> t, std::string& name){
    std::vector<std::shared_ptr<VarDecl>> a = args();

    if (accept(TT::LBRA)) {
        return std::make_shared<FuncDecl>(std::move(t), name, a, block());
    }

    if (accept(TT::SC)) {
        consume(TT::SC, "");
        return std::make_shared<FunProto>(std::move(t), name, a);
    }

    throw parsing_exception("Expected ';' or block declaration after function", peek(0));
}

std::shared_ptr<VarDecl> Parser::vardecl(){
    std::shared_ptr<Type> t = type();
    std::string name = consume(TT::IDENTIFIER, "Expected identifier in variable declaration")->value;
    array(t);
    consume(TT::SC, "Expected ';' after variable declaration");
    return std::make_shared<VarDecl>(std::move(t), name);
}

std::shared_ptr<StructDecl> Parser::structdecl(){
    consume(TT::STRUCT, "Expected 'struct' in struct declaration");
    std::string name = consume(TT::IDENTIFIER, "Expected identifier in struct declaration")->value;
    consume(TT::LBRA, "Expected '{' in struct declaration");
    std::shared_ptr<StructDecl> s = std::make_shared<StructDecl>(name);

    while (!accept(TT::RBRA) && !accept(TT::END_OF_FILE)){
        s->varDecls.push_back(vardecl());
    }

    consume(TT::RBRA, "Expected '}' in struct declaration");
    consume(TT::SC, "Expected ';' after struct declaration");

    return s;
}

std::shared_ptr<Decl> Parser::decl(){

    if (accept(TT::STRUCT)){
        return structdecl();
    }

    std::shared_ptr<Type> t = type();
    std::string name = consume(TT::IDENTIFIER, "Expected identifier in declaration")->value;

    if (accept(TT::LSBR)){
        array(t);
    }

    if (accept(TT::SC)){
        consume(TT::SC, "");
        return std::make_shared<VarDecl>(t, name);
    }

    if (accept(TT::LPAR)){
        return funcdecl(std::move(t), name);
    }

    throw parsing_exception("Expected ';' or '( in declaration", peek(0));
}