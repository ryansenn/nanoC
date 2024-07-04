//
// Created by Ryan Senoune on 2024-06-13.
//

#include "parser.h"

std::shared_ptr<Expr> Parser::access(std::shared_ptr<Expr> f){
    while(accept({TT::LSBR, TT::DOT})){
        if(accept(TT::LSBR)){
            consume(TT::LSBR, "");
            f = std::make_shared<Subscript>(std::move(f), expr());
            consume(TT::RSBR, "Expected closing ']'");
        }
        else{
            consume(TT::DOT, "");
            f = std::make_shared<Member>(std::move(f), consume(TT::IDENTIFIER, "Expected identifier for struct member access")->value);
        }
    }
    return f;
}

std::shared_ptr<Expr> Parser::funccall(){
    std::shared_ptr<Token> t = consume(TT::IDENTIFIER, "Expected identifier in function call");
    consume(TT::LPAR, "Expected '(' in function call");
    std::shared_ptr<Call> c = std::make_shared<Call>(std::move(t));

    while (!accept({TT::END_OF_FILE, TT::RPAR})) {
        c->args.push_back(expr());
        if (accept(TT::RPAR)) {
            break;
        }
        consume(TT::COMMA, "Expected comma in between function call arguments");
    }
    consume(TT::RPAR, "Expected ')' after function call args");

    return c;
}

std::shared_ptr<Expr> Parser::unary(){
    if (accept({TT::MINUS, TT::ASTERISK, TT::AND, TT::NOT})){
        std::shared_ptr<Token> op = consume({TT::MINUS, TT::ASTERISK, TT::AND, TT::NOT},"");
        op->value = "op";
        if (accept(TT::MINUS)){
            throw parsing_exception("Expected primary non unary expression", peek(0));
        }
        return std::make_shared<Unary>(std::move(op), factor());
    }
    else {
        consume(TT::LPAR, "Expected '(' before type cast");
        std::shared_ptr<Type> t = type();
        consume(TT::RPAR, "Expected ')' after type cast");
        return std::make_shared<TypeCast>(std::move(t), factor());
    }
}



std::shared_ptr<Expr> Parser::factor(){
    std::shared_ptr<Expr> f;

    if (accept({TT::MINUS, TT::ASTERISK, TT::AND, TT::NOT}) || accept(TT::LPAR) && accept({TT::STRUCT,TT::INT,TT::CHAR,TT::VOID},1)){
        f = unary();
    }

    else if (accept({TT::INT_LITERAL, TT::CHAR_LITERAL, TT::STRING_LITERAL})){
        f = std::make_shared<Primary>(std::move(consume(peek(0)->token_type, "")));
    }

    else if (accept(TT::IDENTIFIER)) {
        if (peek(1)->token_type == TT::LPAR){
            f = funccall();
        }
        else{
            f = std::make_shared<Primary>(consume(TT::IDENTIFIER, ""));
        }
    }

    else if (accept(TT::LPAR)){
        consume(TT::LPAR, "");
        f = expr();
        consume(TT::RPAR, "Expected closing parenthesis");
    }

    else{
        throw parsing_exception("Expected primary expression (int lit, char lit, string lit, identifier or func call)", peek(0));
    }

    return access(f);
}

std::shared_ptr<Expr> Parser::term(){
    std::shared_ptr<Expr> e1 = factor();

    while (accept({TT::ASTERISK, TT::DIV, TT::REM})){
        std::shared_ptr<Token> op = consume({TT::ASTERISK, TT::DIV, TT::REM}, "");
        std::shared_ptr<Expr> e2 = factor();

        e1 = std::make_shared<Binary>(std::move(e1), std::move(op), std::move(e2));
    }

    return e1;
}

std::shared_ptr<Expr> Parser::sum(){
    std::shared_ptr<Expr> e1 = term();

    while (accept({TT::PLUS, TT::MINUS})){
        std::shared_ptr<Token> op = consume({TT::PLUS, TT::MINUS}, "");
        std::shared_ptr<Expr> e2 = term();

        e1 = std::make_shared<Binary>(std::move(e1), std::move(op), std::move(e2));
    }

    return e1;
}

std::shared_ptr<Expr> Parser::comparison(){
    std::shared_ptr<Expr> e1 = sum();

    while (accept({TT::GE, TT::GT, TT::LE, TT::LT})){
        std::shared_ptr<Token> op = consume({TT::GE, TT::GT, TT::LE, TT::LT}, "");
        std::shared_ptr<Expr> e2 = sum();

        e1 = std::make_shared<Binary>(std::move(e1), std::move(op), std::move(e2));
    }

    return e1;
}

std::shared_ptr<Expr> Parser::equality(){
    std::shared_ptr<Expr> e1 = comparison();

    while (accept({TT::EQ, TT::NE})){
        std::shared_ptr<Token> op = consume({TT::EQ, TT::NE}, "");
        std::shared_ptr<Expr> e2 = comparison();

        e1 = std::make_shared<Binary>(std::move(e1), std::move(op), std::move(e2));
    }

    return e1;
}

std::shared_ptr<Expr> Parser::logor(){
    std::shared_ptr<Expr> e1 = equality();

    while (accept(TT::LOGOR)){
        std::shared_ptr<Token> op = consume(TT::LOGOR, "");
        std::shared_ptr<Expr> e2 = equality();

        e1 = std::make_shared<Binary>(std::move(e1), std::move(op), std::move(e2));
    }

    return e1;
}

std::shared_ptr<Expr> Parser::logand(){
    std::shared_ptr<Expr> e1 = logor();

    while (accept(TT::LOGAND)){
        std::shared_ptr<Token> op = consume(TT::LOGAND, "");
        std::shared_ptr<Expr> e2 = logor();

        e1 = std::make_shared<Binary>(std::move(e1), std::move(op), std::move(e2));
    }

    return e1;
}

std::shared_ptr<Expr> Parser::assignment(){
    std::shared_ptr<Expr> e1 = logand();

    if (accept(TT::ASSIGN)){
        std::shared_ptr<Token> op = consume(TT::ASSIGN, "");
        std::shared_ptr<Expr> e2 = assignment();

        e1 = std::make_shared<Binary>(std::move(e1), std::move(op), std::move(e2));
    }

    return e1;
}

// equality, comparison, term, factor, unary, primary
std::shared_ptr<Expr> Parser::expr(){
    return assignment();
}
