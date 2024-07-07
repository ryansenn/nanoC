//
// Created by Ryan Senoune on 2024-06-30.
//

#include "type_analysis.h"



void TypeAnalysis::visit(std::shared_ptr<Primary> p) {
    switch (p->token->token_type) {
        case TT::IDENTIFIER:
            p->type = std::make_shared<Type>(*(std::dynamic_pointer_cast<VarDecl>(p->symbol->decl)->type));
            p->lvalue = true;
            break;
        case TT::INT_LITERAL:
            p->type = std::make_shared<Type>(std::make_shared<Token>(TT::INT));
            break;
        case TT::CHAR_LITERAL:
            p->type = std::make_shared<Type>(std::make_shared<Token>(TT::CHAR));
            break;
        case TT::STRING_LITERAL:
            p->type = std::make_shared<Type>(std::make_shared<Token>(TT::CHAR));
            p->type->arraySize.push_back(p->token->value.size()+1);
            break;
        default:
            break;
    }
}

void TypeAnalysis::visit(std::shared_ptr<Unary> u) {
    u->expr1->accept(*this);
    u->type = std::make_shared<Type>(*(u->expr1->type));
    switch (u->op->token_type) {
        case TT::MINUS:
        case TT::NOT:
            if (u->expr1->type->str() != "int"){
                throw semantic_exception("Invalid unary type '" + u->expr1->type->str() + "' but expected type 'int'",u->op);
            }
            break;
        case TT::ASTERISK:
            if (u->expr1->type->pointerCount == 0){
                throw semantic_exception("Dereferencing non-pointer '" + u->expr1->type->str() + "'", u->op);
            }
            u->type->pointerCount--;
            u->lvalue = true;
            break;
        case TT::AND:
            if (!u->expr1->lvalue){
                throw semantic_exception("Cannot reference non-lvalue expression", u->op);
            }
            u->type->pointerCount++;
            break;
        default:
            break;
    }
}

void TypeAnalysis::visit(std::shared_ptr<Binary> b) {
    b->expr1->accept(*this);
    b->expr2->accept(*this);
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
            break;
        case TT::NE:
        case TT::EQ:
            if (b->expr1->type->token->token_type == TT::STRUCT || b->expr2->type->token->token_type == TT::STRUCT){
                throw semantic_exception("Invalid operand type for binary operator '" + getTokenName(b->op->token_type) + "'", b->op);
            }
            b->type = std::make_shared<Type>(std::make_shared<Token>(TT::INT));
            break;
        case TT::ASSIGN:
            if (*(b->expr1->type) != *(b->expr2->type)){
                throw semantic_exception("Incompatible types when initializing type '" + b->expr1->type->str() + "' using type '" + b->expr2->type->str() + "'" , b->op);
            }
            if (!b->expr1->lvalue){
                throw semantic_exception("lvalue required as left operand of assignment", b->op);
            }
            b->type = std::make_shared<Type>(*(b->expr2->type));
            break;
        default:
            break;
    }
}

void TypeAnalysis::visit(std::shared_ptr<Subscript> s) {
    s->array->accept(*this);
    s->index->accept(*this);
    if (s->array->type->pointerCount == 0 && s->array->type->arraySize.size() == 0){
        throw semantic_exception("Array subscript operator requires an array or pointer type but found '" + s->array->type->str() + "'", s->token);
    }

    if (s->index->type->str() != "int"){
        throw semantic_exception("Array index must be an integer type but found '" + s->index->type->str() + "'", s->token);
    }

    s->type = std::make_shared<Type>(*(s->array->type));
    s->type->arraySize.clear();
    for (int i=0;i<s->array->type->arraySize.size()-1;i++){
        s->type->arraySize.push_back(s->array->type->arraySize[i]);
    }

    s->lvalue = s->array->lvalue;
}

void TypeAnalysis::visit(std::shared_ptr<Member> m) {
    m->structure->accept(*this);
    m->lvalue = m->structure->lvalue;
    if (m->structure->type->token->token_type != TT::STRUCT || m->structure->type->pointerCount > 0 || m->structure->type->arraySize.size() > 0){
        throw semantic_exception("Left operand of '.' operator must be a structure but found '" + m->structure->type->str() + "'", m->token);
    }
    std::shared_ptr<StructDecl> structDecl = std::dynamic_pointer_cast<StructDecl>(m->structure->type->symbol->decl);
    for (auto v : structDecl->varDecls){
        if (v->name == m->member){
            m->type = std::make_shared<Type>(*(v->type));
            return;
        }
    }
    throw semantic_exception("Struct '" + structDecl->name + "' has no member named '" + m->member + "'", m->token);
}

void TypeAnalysis::visit(std::shared_ptr<TypeCast> t) {
    t->expr1->accept(*this);
    if ((t->expr1->type->str() == "char" && t->typeCast->str() == "int") || (t->expr1->type->pointerCount > 0 && t->typeCast->pointerCount > 0)){
        t->type = std::make_shared<Type>(*t->typeCast);
    }
    else {
        throw semantic_exception("Invalid type cast from '" + t->expr1->type->str() + "' to '" + t->typeCast->str() + "'", t->typeCast->token);
    }
}

void TypeAnalysis::visit(std::shared_ptr<Call> call) {
    for (auto a : call->args){
        a->accept(*this);
    }
    std::shared_ptr<FuncDecl> funcDecl = std::dynamic_pointer_cast<FuncDecl>(call->symbol->decl);
    if (call->args.size() != funcDecl->args.size()){
        throw semantic_exception("Too few/many arguments in function '" + call->identifier->value + "' call", call->identifier);
    }

    for(int i=0;i<call->args.size();i++){
        if (*(call->args[i]->type) != *(funcDecl->args[i]->type)){
            throw semantic_exception("Type mismatch in function '" + call->identifier->value + "' call, argument '" + funcDecl->args[i]->name + "' expected type '" + funcDecl->args[i]->type->str() + "' but received '" + call->args[i]->type->str() + "'", call->identifier);
        }
    }

    call->type = std::make_shared<Type>(*(funcDecl->type));
}

void TypeAnalysis::visit(std::shared_ptr<VarDecl> varDecl) {
    if (varDecl->type->token->token_type == TT::VOID && varDecl->type->pointerCount == 0){
        throw semantic_exception("Declaration of variable '" + varDecl->name + "' of type void", varDecl->type->token);
    }
}

void TypeAnalysis::visit(std::shared_ptr<While> w) {
    w->expr->accept(*this);
    w->stmt->accept(*this);
    if (w->expr->type->str() != "int"){
        throw semantic_exception("While condition must be an integer", w->token);
    }
}

void TypeAnalysis::visit(std::shared_ptr<If> i) {
    i->expr1->accept(*this);
    i->stmt1->accept(*this);
    if (i->stmt2.has_value()){
        i->stmt2->get()->accept(*this);
    }
    if (i->expr1->type->str() != "int"){
        throw semantic_exception("If condition expression must be an integer", i->token);
    }
}

void TypeAnalysis::visit(std::shared_ptr<Return> r) {

    if (r->expr.has_value()){
        r->expr->get()->accept(*this);
    }

    std::shared_ptr<FuncDecl> funcDecl = std::dynamic_pointer_cast<FuncDecl>(r->funcDecl->decl);
    if ((r->expr.has_value() && (*(funcDecl->type) != *(r->expr->get()->type))) || (!r->expr.has_value() && funcDecl->type->str() != "void")){
        throw semantic_exception("Return type mismatch: expected '" + funcDecl->type->str() + "', but found '" + r->expr->get()->type->str() + "'", r->token);
    }

}

void TypeAnalysis::visit(std::shared_ptr<Program> p) {
    for(auto d : p->decls){
        d->accept(*this);
    }
}


void TypeAnalysis::visit(std::shared_ptr<Block> b) {
    for (auto s : b->stmts){
        s->accept(*this);
    }
}

void TypeAnalysis::visit(std::shared_ptr<FuncDecl> p) {
    for (auto a : p->args){
        a->accept(*this);
    }

    p->block->accept(*this);
}
void TypeAnalysis::visit(std::shared_ptr<FunProto> p) {
    for (auto a : p->args){
        a->accept(*this);
    }
}
void TypeAnalysis::visit(std::shared_ptr<StructDecl> p) {
    for (auto d : p->varDecls){
        if (d->type->name == p->name && d->type->pointerCount == 0){
            throw semantic_exception("Recursive reference '" + d->name + "' without a pointer in struct '"+ p->name +"'", d->type->token);
        }
        d->accept(*this);
    }
}
void TypeAnalysis::visit(std::shared_ptr<Break> p) {}
void TypeAnalysis::visit(std::shared_ptr<Continue> p) {}
void TypeAnalysis::visit(std::shared_ptr<Type> p) {}
