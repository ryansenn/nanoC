//
// Created by Ryan Senoune on 2024-06-30.
//

#include "type_analysis.h"

void TypeAnalysis::expect(std::shared_ptr<Type> actual, TT expected) {
    if (actual->token->token_type != expected){
        throw semantic_exception("Invalid type '" + actual->str() + "' but found type '" + getTokenName(expected) + "'",actual->token);
    }
}

void TypeAnalysis::expect(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {

}

void TypeAnalysis::visit(std::shared_ptr<Primary> p) {
    switch (p->token->token_type) {
        case TT::IDENTIFIER:
            p->type = std::dynamic_pointer_cast<VarDecl>(p->symbol->decl)->type;
        case TT::INT_LITERAL:
            p->type = std::make_shared<Type>(std::make_shared<Token>(TT::INT));
        case TT::CHAR_LITERAL:
            p->type = std::make_shared<Type>(std::make_shared<Token>(TT::CHAR));
        case TT::STRING_LITERAL:
            p->type = std::make_shared<Type>(std::make_shared<Token>(TT::CHAR));
            p->type->pointerCount = 1;
        default:
            break;
    }
}

void TypeAnalysis::visit(std::shared_ptr<Unary> u) {
    u->type = std::make_shared<Type>(*(u->expr1->type));
    switch (u->op->token_type) {
        case TT::MINUS:
        case TT::NOT:
            expect(u->type, TT::INT);
        case TT::ASTERISK:
            if (u->expr1->type->pointerCount == 0){
                throw semantic_exception("Dereferencing non-pointer '" + u->expr1->type->str() + "'", u->expr1->type->token);
            }
            u->type->pointerCount--;
        case TT::AND:
            u->type->pointerCount++;
        default:
            break;
    }
}

void TypeAnalysis::visit(std::shared_ptr<VarDecl> varDecl) {
    if (varDecl->type->token->token_type == TT::VOID && varDecl->type->pointerCount == 0){
        throw semantic_exception("declaration of variable '" + varDecl->name + "' of type void", varDecl->type->token);
    }
}

void TypeAnalysis::visit(std::shared_ptr<Call> call) {
    std::shared_ptr<FuncDecl> funcDecl = std::dynamic_pointer_cast<FuncDecl>(call->symbol->decl);
    if (call->args.size() != funcDecl->args.size()){
        throw semantic_exception("Too few/many arguments in function '" + call->identifier->value + "'", call->identifier);
    }

    for(int i=0;i<call->args.size();i++){
        if (*(call->args[i]->type) != *(funcDecl->args[i]->type)){
            throw semantic_exception("Incompatible type in function call '" + call->identifier->value + "', expected ");
        }
    }

}
