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


#endif //COMPILER_SYMBOL_H
