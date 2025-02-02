cmake_minimum_required(VERSION 3.28)
project(compiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(compiler main.cpp
        lexer/lexer.cpp
        lexer/token.cpp
        parser/parser.cpp
        parser/decl.cpp
        parser/stmt.cpp
        parser/expr.cpp
        semantic/name_analysis.cpp
        parser/ast.cc
        semantic/type_analysis.cpp
        x86/code_gen_deprecate.cpp
        memory/memory_allocation.cpp
        x86/addr_gen.cpp
        ir/cfg_gen.cpp
)
