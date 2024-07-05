//
// Created by Ryan Senoune on 2024-06-30.
//

#include "type_analysis.h"



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
            if (u->expr1->type->str() != "int"){
                throw semantic_exception("Invalid unary type '" + u->expr1->type->str() + "' but expected type 'int'",u->op);
            }
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

void TypeAnalysis::visit(std::shared_ptr<Binary> b) {
    switch (b->op->token_type) {
        case TT::PLUS:
        case TT::MINUS:
        case TT::ASTERISK:
        case TT::DIV:
        case TT::LOGAND:
        case TT::LOGOR:
        case TT::GT:
        case TT::GE:
        case TT::LT:
        case TT::LE:
            if (b->expr1->type->str() != "int" || b->expr2->type->str() != "int"){
                throw semantic_exception("Invalid operand type for binary operator '" + getTokenName(b->op->token_type) + "'", b->op);
            }
            b->type = std::make_shared<Type>(*(b->expr1->type));
        case TT::NE:
        case TT::EQ:
            if (b->expr1->type->token->token_type == TT::STRUCT || b->expr2->type->token->token_type == TT::STRUCT){
                throw semantic_exception("Invalid operand type for binary operator '" + getTokenName(b->op->token_type) + "'", b->op);
            }
            b->type = std::make_shared<Type>(std::make_shared<Token>(TT::INT));
        default:
            break;
    }
}

void TypeAnalysis::visit(std::shared_ptr<Subscript> s) {
    if (s->array->type->pointerCount == 0 && s->array->type->arraySize.size() == 0){
        throw semantic_exception("Array subscript operator requires an array or pointer type but found '" + s->array->type->str() + "'", s->array->type->token);
    }

    if (s->index->type->str() != "int"){
        throw semantic_exception("Array index must be an integer type but found '" + s->index->type->str() + "'", s->index->type->token);
    }

    s->type = std::make_shared<Type>(std::make_shared<Token>(TT::INT));
}

void TypeAnalysis::visit(std::shared_ptr<Member> m) {
    if (m->structure->type->token->token_type != TT::STRUCT || m->structure->type->pointerCount > 0 || m->structure->type->arraySize.size() > 0){
        throw semantic_exception("Left operand of '.' operator must be a structure but found '" + m->structure->type->str() + "'", m->structure->type->token);
    }
}

void TypeAnalysis::visit(std::shared_ptr<TypeCast> t) {
    if ((t->expr1->type->str() == "char" && t->typeCast->str() == "int") || (t->expr1->type->pointerCount > 0 && t->typeCast->pointerCount > 0)){
        t->type = std::make_shared<Type>(*t->typeCast);
    }
    else {
        throw semantic_exception("Invalid type cast from '" + t->expr1->type->str() + "' to '" + t->typeCast->str() + "'", t->typeCast->token);
    }
}

void TypeAnalysis::visit(std::shared_ptr<VarDecl> varDecl) {
    if (varDecl->type->token->token_type == TT::VOID && varDecl->type->pointerCount == 0){
        throw semantic_exception("Declaration of variable '" + varDecl->name + "' of type void", varDecl->type->token);
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

    call->type = std::make_shared<Type>(*(funcDecl->type));
}

void TypeAnalysis::visit(std::shared_ptr<FuncDecl> p) {}
void TypeAnalysis::visit(std::shared_ptr<FunProto> p) {}
void TypeAnalysis::visit(std::shared_ptr<StructDecl> p) {}
void TypeAnalysis::visit(std::shared_ptr<If> p) {}
void TypeAnalysis::visit(std::shared_ptr<Block> p) {}
void TypeAnalysis::visit(std::shared_ptr<Break> p) {}
void TypeAnalysis::visit(std::shared_ptr<While> p) {}
void TypeAnalysis::visit(std::shared_ptr<Return> p) {}
void TypeAnalysis::visit(std::shared_ptr<Continue> p) {}
void TypeAnalysis::visit(std::shared_ptr<Type> p) {}
void TypeAnalysis::visit(std::shared_ptr<Program> p) {}
