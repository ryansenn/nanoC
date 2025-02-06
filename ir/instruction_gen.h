//
// Created by Ryan Senoune on 2025-02-01.
//

#ifndef COMPILER_INSTRUCTION_GEN_H
#define COMPILER_INSTRUCTION_GEN_H


#include "../parser/ast.h"
#include "ir.h"

class InstructionGen : public Visitor<std::shared_ptr<Register>>{
public:

    std::vector<std::shared_ptr<Instruction>> instructions;
    std::shared_ptr<VirtualRegister> NO_REGISTER = nullptr;

    int label_id = 0;
    std::string return_label = "";

    std::unordered_map<std::shared_ptr<VarDecl>, std::shared_ptr<VirtualRegister>> symbol_table;

    void emit(std::string opcode, std::shared_ptr<Register> r1, std::shared_ptr<Register> r2);
    void emit(std::string opcode, std::shared_ptr<Register> r1);
    void emit(std::string opcode, std::shared_ptr<Register> r1, std::string value);
    void emit(std::string opcode);
    void emit_branch(std::string opcode, std::string label);
    void emit_branch(std::string opcode, std::shared_ptr<Register> r1);
    void emit_label(std::string label, bool isFunc);

    std::shared_ptr<VirtualRegister> getRegister();
    std::string getLabel(std::string name);

    std::shared_ptr<Register> visit(std::shared_ptr<Program>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<FuncDecl>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Block>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Return>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<If>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<While>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Break>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Continue>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<VarDecl>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Subscript>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Member>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Call>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Primary>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Unary>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<TypeCast>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Binary>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<Type>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<FunProto>) override;
    std::shared_ptr<Register> visit(std::shared_ptr<StructDecl>) override;
};


#endif //COMPILER_INSTRUCTION_GEN_H
