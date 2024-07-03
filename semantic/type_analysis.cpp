//
// Created by Ryan Senoune on 2024-06-30.
//

#include "type_analysis.h"

void TypeAnalysis::visit(std::shared_ptr<VarDecl> varDecl) {
    if (varDecl->type->token->token_type == TT::VOID && varDecl->type->pointerCount == 0){
        throw semantic_exception("declaration of variable '" + varDecl->name + "' of type void", varDecl->type->token);
    }
}

bool TypeAnalysis::match_type(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected){
    if (!(actual->token->token_type == expected->token->token_type && actual->name == expected->name && actual->pointerCount == expected->pointerCount && actual->arraySize == expected->arraySize)){
            throw semantic_exception("Expected argument of type  '" + expected->name + "'", actual->token);
    }
}

bool TypeAnalysis::match_args(std::vector<std::shared_ptr<Expr>> call, std::vector<std::shared_ptr<VarDecl>> args){
    for(int i=0;i<call.size();i++){
        match_type(call[i]->type, args[i]->type);
    }
}

void TypeAnalysis::visit(std::shared_ptr<Call> call) {
    std::shared_ptr<FuncDecl> funcDecl = std::get<std::shared_ptr<FuncDecl>>(call->symbol->decl);
    if (call->args.size() != funcDecl->args.size()){
        throw semantic_exception("Too few/many arguments in function '" + call->identifier->value + "'", call->identifier);
    }

    match_args(call->args, funcDecl->args);

}
