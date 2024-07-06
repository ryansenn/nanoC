//
// Created by Ryan Senoune on 2024-06-13.
//

#include "parser.h"

std::shared_ptr<Block> Parser::block(){
    consume(TT::LBRA, "Expected '{' in block declaration");
    std::vector<std::shared_ptr<Stmt>> stmts;

    while (!accept({TT::RBRA, TT::END_OF_FILE})){
        stmts.push_back(stmt());
    }

    consume(TT::RBRA, "Expected '}' in block declaration");

    return std::make_shared<Block>(std::move(stmts));
}

std::shared_ptr<Stmt> Parser::stmt(){
    switch (peek(0)->token_type) {
        case TT::INT:
        case TT::CHAR:
        case TT::VOID:
        case TT::STRUCT:
        {
            return vardecl();
        }
        case TT::LBRA:
            return block();
        case TT::WHILE: {
            std::shared_ptr<Token> token = consume(TT::WHILE, "");
            return std::make_shared<While>(expr(), stmt(), std::move(token));
        }
        case TT::IF: {
            std::shared_ptr<Token> token = consume(TT::IF,"");
            std::shared_ptr<Expr> e = expr();
            std::shared_ptr<Stmt> s1 = stmt();
            if (accept(TT::ELSE)) {
                consume(TT::ELSE, "");
                return std::make_shared<If>(std::move(e), std::move(s1), stmt(), std::move(token));
            }
            return std::make_shared<If>(std::move(e), std::move(s1), std::move(token));
        }
        case TT::CONTINUE:
            consume(TT::CONTINUE, "");
            consume(TT::SC, "Expected ';' after continue");
            return std::make_shared<Continue>();
        case TT::BREAK:
            consume(TT::BREAK, "");
            consume(TT::SC, "Expected ';' after break");
            return std::make_shared<Break>();
        case TT::RETURN:
        {
            std::shared_ptr<Token> token = consume(TT::RETURN, "");
            std::shared_ptr<Return> r = std::make_shared<Return>(std::move(token));
            if (!accept(TT::SC)){
                r->expr = expr();
            }
            consume(TT::SC, "Expected ';' after return");
            return r;
        }
        default:
            std::shared_ptr<Expr> e = expr();
            consume(TT::SC, "Expected ';' after expression statement");
            return e;
    }
}

