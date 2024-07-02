//
// Created by Ryan Senoune on 2024-06-30.
//

#include "type_analysis.h"

void TypeAnalysis::visit(std::shared_ptr<VarDecl> varDecl) {
    if (varDecl->type->token->token_type == TT::VOID && varDecl->type->pointerCount == 0){
        throw semantic_exception("declaration of variable '" + varDecl->name + "' of type void", varDecl->type->token);
    }
}

bool TypeAnalysis::match_type(std::shared_ptr<Type> t1, std::shared_ptr<Type> t2){
    return t1->token->token_type == t2->token->token_type && t1->name == t2->name && t1->pointerCount == t2->pointerCount && t1->arraySize == t2->arraySize;
}

bool TypeAnalysis::match_args(std::vector<std::shared_ptr<Expr>> call, std::vector<std::shared_ptr<VarDecl>> args){
    for(int i=0;i<call.size();i++){
        if (!match_type(call[i])){

        }
    }
}

void TypeAnalysis::visit(std::shared_ptr<Call> call) {
    std::shared_ptr<FuncDecl> funcDecl = std::get<std::shared_ptr<FuncDecl>>(call->symbol->decl);
    if (call->args.size() != funcDecl->args.size()){
        throw semantic_exception("Too few/many arguments in function '" + call->identifier->value + "'", call->identifier);
    }

    if (!match_args(call->args, funcDecl->args)){

    }
}
