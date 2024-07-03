//
// Created by Ryan Senoune on 2024-06-30.
//

#include "type_analysis.h"

void TypeAnalysis::visit(std::shared_ptr<VarDecl> varDecl) {
    if (varDecl->type->token->token_type == TT::VOID && varDecl->type->pointerCount == 0){
        throw semantic_exception("declaration of variable '" + varDecl->name + "' of type void", varDecl->type->token);
    }
}

void TypeAnalysis::visit(std::shared_ptr<Call> call) {
    std::shared_ptr<FuncDecl> funcDecl = std::get<std::shared_ptr<FuncDecl>>(call->symbol->decl);
    if (call->args.size() != funcDecl->args.size()){
        throw semantic_exception("Too few/many arguments in function '" + call->identifier->value + "'", call->identifier);
    }

    for(int i=0;i<call->args.size();i++){
        if (*(call->args[i]->type) != *(funcDecl->args[i]->type)){
            throw semantic_exception("Incompatible type in function call '" + call->identifier->value + "', expected " + , call->identifier);
        }
    }

}
