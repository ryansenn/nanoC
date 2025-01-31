//
// Created by Ryan Senoune on 2025-01-29.
//

#ifndef COMPILER_CFG_GEN_H
#define COMPILER_CFG_GEN_H


#include "../parser/ast.h"

class VirtualRegister {
public:
    static int count;
    int id;
    VirtualRegister() : id(count++) {}
};

class Instruction{
public:
    std::string opcode;
    std::vector<std::shared_ptr<VirtualRegister>> registers;
    std::string value;
    std::string label;

    Instruction(std::string opcode, std::vector<std::shared_ptr<VirtualRegister>> registers) :
                opcode(opcode), registers(registers) {}

    Instruction(std::string opcode, std::vector<std::shared_ptr<VirtualRegister>> registers, std::string value) :
                opcode(opcode), registers(registers), value(value) {}

};

class BasicBlock {
public:
    static int count;
    int id;
    std::vector<std::shared_ptr<Instruction>> instructions;
    std::vector<std::shared_ptr<BasicBlock>> successors;
    BasicBlock() : id(count++) {}
};

class CFG {
public:
    std::string name;
    std::shared_ptr<BasicBlock> entry;
    std::shared_ptr<BasicBlock> exit;
    CFG(std::string name) : name(name) {}
};

class cfg_gen : public Visitor<std::shared_ptr<VirtualRegister>> {
public:

    std::vector<std::shared_ptr<CFG>> results;

    std::shared_ptr<CFG> curr_cfg;
    std::shared_ptr<BasicBlock> curr_block;
    std::shared_ptr<VirtualRegister> NO_REGISTER = nullptr;

    std::unordered_map<std::shared_ptr<VarDecl>, std::shared_ptr<VirtualRegister>> symbol_table;

    void emit(std::string opcode, std::shared_ptr<VirtualRegister> r1, std::shared_ptr<VirtualRegister> r2);
    void emit(std::string opcode, std::shared_ptr<VirtualRegister> r1);
    void emit(std::string opcode, std::shared_ptr<VirtualRegister> r1, std::string value);

    std::shared_ptr<VirtualRegister> getRegister();

    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Program>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<FuncDecl>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Block>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Return>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<If>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<While>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Break>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Continue>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<VarDecl>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Subscript>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Member>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Call>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Primary>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Unary>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<TypeCast>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Binary>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<Type>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<FunProto>) override;
    std::shared_ptr<VirtualRegister> visit(std::shared_ptr<StructDecl>) override;
};



#endif //COMPILER_CFG_GEN_H
