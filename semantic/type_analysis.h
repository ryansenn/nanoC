//
// Created by Ryan Senoune on 2024-06-30.
//

#ifndef COMPILER_TYPE_ANALYSIS_H
#define COMPILER_TYPE_ANALYSIS_H

#include "../parser/ast.h"
#include "semantic_exception.h"


class TypeAnalysis : public Visitor{

    void expect(std::shared_ptr<Type> actual, TT expected);
    void expect(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected);

    void visit(std::shared_ptr<FuncDecl> func) override;
    void visit(std::shared_ptr<FunProto> funProto) override;
    void visit(std::shared_ptr<Call> call) override;
    void visit(std::shared_ptr<VarDecl> varDecl) override;
    void visit(std::shared_ptr<Primary> primary) override;
    void visit(std::shared_ptr<StructDecl> structDecl) override;
    void visit(std::shared_ptr<Unary> unary) override;
    void visit(std::shared_ptr<Binary> binary) override;
    void visit(std::shared_ptr<Subscript> subscript) override;
    void visit(std::shared_ptr<Member> member) override;
    void visit(std::shared_ptr<Block> block) override;
    void visit(std::shared_ptr<If> i) override;
    void visit(std::shared_ptr<While> w) override;
    void visit(std::shared_ptr<Return> ret) override;
    void visit(std::shared_ptr<Program> program) override;
    void visit(std::shared_ptr<Continue> c) override;
    void visit(std::shared_ptr<Break> b) override;
    void visit(std::shared_ptr<Type> type) override;
};


#endif //COMPILER_TYPE_ANALYSIS_H
