//
// Created by Ryan Senoune on 2024-06-17.
//

#ifndef COMPILER_SYMBOL_H
#define COMPILER_SYMBOL_H

#include "../parser/ast.h"
#include "semantic_exception.h"

struct Symbol : std::enable_shared_from_this<Symbol>{
    enum class Type{ VAR, FUNC, PROTO, STRUCT };

    Type type;
    std::shared_ptr<Decl> decl;

    Symbol(Type type, std::shared_ptr<Decl> decl) : type(type), decl(decl) {}
};

class Analysis : public Visitor{

    std::vector<std::unordered_map<std::string, std::shared_ptr<Symbol>>> scopes;

    std::shared_ptr<Symbol> get(std::string identifier){
        for (int i=scopes.size()-1;i>=0;i--){
            if (scopes[i].find(identifier) != scopes[i].end()){
                return scopes[i][identifier];
            }
        }
        return std::shared_ptr<Symbol>(nullptr);
    }

    std::shared_ptr<Symbol> get_local(std::string identifier){
        if (scopes[scopes.size()-1].find(identifier) != scopes[scopes.size()-1].end()){
            return scopes[scopes.size()-1][identifier];
        }

        return std::shared_ptr<Symbol>(nullptr);
    }

    void put(std::string identifier, std::shared_ptr<Symbol> symbol){
        scopes[scopes.size()-1][identifier] = symbol;
    }

    void visit(std::shared_ptr<FuncDecl> func) override{

        if (get_local(func->name)){
            if (get_local(func->name)->type == Symbol::Type::PROTO){
                get_local(func->name)->type = Symbol::Type::FUNC;
                get_local(func->name)->decl = func;
            }
            else{
                throw semantic_exception("Identifier '" + func->name + "' has already been declared in the same scope", func->type->token);
            }
        }

        put(func->name, std::make_shared<Symbol>(Symbol::Type::FUNC, func));

        func->block->accept(*this);
    }

    void visit(std::shared_ptr<FunProto> funProto) override{
        if (!get(funProto->name)){
            put(funProto->name, std::make_shared<Symbol>(Symbol::Type::PROTO, funProto));
        }
    }

    void visit(std::shared_ptr<Call> call) override{
        std::shared_ptr<Symbol> funcDecl = get(call->identifier->value);

        if (!funcDecl){
            throw semantic_exception("Function '" + call->identifier->value + "' is not declared", call->identifier);
        }

        call->symbol = funcDecl;
    }

    void visit(std::shared_ptr<VarDecl> varDecl) override{
        if (get_local(varDecl->name)){
             throw semantic_exception("Identifier '" + varDecl->name + "' has already been declared in the same scope", varDecl->type->token);
        }

        put(varDecl->name, std::make_shared<Symbol>(Symbol::Type::VAR, varDecl));
    }

    void visit(std::shared_ptr<Primary> primary) override{
        if (primary->token->token_type == TT::IDENTIFIER){
            std::shared_ptr<Symbol> varDecl = get(primary->token->value);

            if (!varDecl){
                throw semantic_exception("Variable '" + primary->token->value + "' is not declared", primary->token);
            }

            primary->symbol = varDecl;
        }
    }

    void visit(std::shared_ptr<StructDecl> structDecl) override{
        for(auto v : structDecl->varDecls){
            v->accept(*this);
        }
    }

    void visit(std::shared_ptr<class Unary> unary) override{
        unary->expr1->accept(*this);
    }

    void visit(std::shared_ptr<class Binary> binary) override{
        binary->expr1->accept(*this);
        binary->expr2->accept(*this);
    }

    void visit(std::shared_ptr<Subscript> subscript) override{
        subscript->array->accept(*this);
        subscript->index->accept(*this);
    }

    void visit(std::shared_ptr<Member> member) override{
        member->structure->accept(*this);
    }

    void visit(std::shared_ptr<Block> block) override{
        scopes.emplace_back();
        for (auto s : block->stmts){
            s->accept(*this);
        }
        scopes.pop_back();
    }

    void visit(std::shared_ptr<If> i) override{
        i->expr1->accept(*this);
        scopes.emplace_back();
        i->stmt1->accept(*this);
        scopes.pop_back();
        scopes.emplace_back();
        i->stmt1->accept(*this);
        scopes.pop_back();
    }

    void visit(std::shared_ptr<While> w) override{
        w->expr->accept(*this);
        scopes.emplace_back();
        w->stmt->accept(*this);
        scopes.pop_back();
    }

    void visit(std::shared_ptr<Return> ret) override{
        if (ret->expr.has_value()){
            ret->expr->get()->accept(*this);
        }
    }

    void visit(std::shared_ptr<Program> program) override{
        scopes.emplace_back();
        for (auto d : program->decls){
            d->accept(*this);
        }
        scopes.pop_back();
    }

    void visit(std::shared_ptr<Continue> c) override{

    }
    void visit(std::shared_ptr<Break> b) override{

    }
    void visit(std::shared_ptr<Type> type) override{

    }

};

#endif //COMPILER_SYMBOL_H
