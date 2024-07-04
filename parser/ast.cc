//
// Created by Ryan Senoune on 2024-07-03.
//

#include "ast.h"

std::ostream& operator<<(std::ostream& os, const Type& type) {
    os << type.token->token_type << " " << type.name;
    for (int i=0;i<type.pointerCount;i++){
        os << "*";
    }
    for (auto p:type.arraySize){
        if (p == -1){
            os << "[]";
        }
        else{
            os << "[" << p << "]";
        }
    }
    return os;
}

std::string Type::str() {
    std::ostringstream oss;
    oss << (*this);
    return oss.str();
}

void PrintVisitor::incr() {
    indent += space;
}

void PrintVisitor::decr() {
    if (indent.size() >= space.size()) {
        indent.erase(indent.size() - space.size());
    }
}

void PrintVisitor::visit(std::shared_ptr<Program> program) {
    std::cout << "Program (" << std::endl;
    incr();
    for (auto d : program->decls) {
        std::cout << indent;
        d->accept(*this);
        std::cout << std::endl;
    }
    decr();
    std::cout << ")";
}

void PrintVisitor::visit(std::shared_ptr<FuncDecl> func) {
    std::cout << "FuncDecl " << func->name << "(";
    bool first = true;
    for (auto a : func->args) {
        if (!first) {
            std::cout << ", ";
        }
        first = false;
        a->accept(*this);
    }
    std::cout << ") (";
    func->type->accept(*this);
    std::cout << ") (" << std::endl;
    incr();
    func->block->accept(*this);
    decr();
    std::cout << indent << ")";
}

void PrintVisitor::visit(std::shared_ptr<FunProto> funProto) {
    std::cout << "FunProto " << funProto->name << "(";
    bool first = true;
    for (auto a : funProto->args) {
        if (!first) {
            std::cout << ", ";
        }
        first = false;
        a->accept(*this);
    }
    std::cout << ") (";
    funProto->type->accept(*this);
    std::cout << ")";
}

void PrintVisitor::visit(std::shared_ptr<Block> block) {
    for (auto s : block->stmts) {
        std::cout << indent;
        s->accept(*this);
        std::cout << std::endl;
    }
}

void PrintVisitor::visit(std::shared_ptr<If> i) {
    std::cout << "If (";
    i->expr1->accept(*this);
    std::cout << ") (" << std::endl;
    incr();
    i->stmt1->accept(*this);
    decr();
    std::cout << indent << ")" << std::endl;

    if (i->stmt2.has_value()) {
        std::cout << indent << "Else (" << std::endl;
        incr();
        i->stmt2->get()->accept(*this);
        decr();
        std::cout << indent << ")" << std::endl;
    }
}

void PrintVisitor::visit(std::shared_ptr<While> w) {
    std::cout << "While (";
    w->expr->accept(*this);
    std::cout << ") (" << std::endl;
    incr();
    w->stmt->accept(*this);
    decr();
    std::cout << indent << ")";
}

void PrintVisitor::visit(std::shared_ptr<Continue> c) {
    std::cout << "Continue";
}

void PrintVisitor::visit(std::shared_ptr<Break> b) {
    std::cout << "Break";
}

void PrintVisitor::visit(std::shared_ptr<Return> ret) {
    std::cout << "return( ";
    incr();
    if (ret->expr.has_value()) {
        ret->expr.value()->accept(*this);
    }
    decr();
    std::cout << " )";
}

void PrintVisitor::visit(std::shared_ptr<VarDecl> varDecl) {
    std::cout << "VarDecl(";
    varDecl->type->accept(*this);
    std::cout << ")";
}

void PrintVisitor::visit(std::shared_ptr<Type> type) {
    std::cout << *type;
}

void PrintVisitor::visit(std::shared_ptr<Call> call) {
    std::cout << "Func Call " << call->identifier->value << " (";
    bool first = true;
    for (auto& arg: call->args) {
        if (!first) {
            std::cout << ", ";
        }
        first = false;
        arg->accept(*this);
    }
    std::cout << " )";
}

void PrintVisitor::visit(std::shared_ptr<StructDecl> structDecl) {
    std::cout << "StructDecl " << structDecl->name << " (";
    for (int i = 0; i < structDecl->varDecls.size(); i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        structDecl->varDecls[i]->accept(*this);
    }
    std::cout << ")";
}

void PrintVisitor::visit(std::shared_ptr<Unary> unary) {
    std::cout << unary->op->token_type;
    std::cout << "(";
    unary->expr1->accept(*this);
    std::cout << ")";
}

void PrintVisitor::visit(std::shared_ptr<TypeCast> typeCast) {
    std::cout << "(";
    typeCast->type->accept(*this);
    std::cout << ")";
    std::cout << "(";
    typeCast->expr1->accept(*this);
    std::cout << ")";
}

void PrintVisitor::visit(std::shared_ptr<Binary> binary) {
    std::cout << "(";
    binary->expr1->accept(*this);
    std::cout << " " << binary->op->token_type << " ";
    binary->expr2->accept(*this);
    std::cout << ")";
}

void PrintVisitor::visit(std::shared_ptr<Primary> primary) {
    std::cout << primary->token->value;
}

void PrintVisitor::visit(std::shared_ptr<Subscript> subscript) {
    std::cout << "(";
    subscript->array->accept(*this);
    std::cout << "[";
    subscript->index->accept(*this);
    std::cout << "]";
    std::cout << ")";
}

void PrintVisitor::visit(std::shared_ptr<Member> member) {
    std::cout << "(";
    member->structure->accept(*this);
    std::cout << "." << member->member;
    std::cout << ")";
}