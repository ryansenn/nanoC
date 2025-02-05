//
// Created by Ryan Senoune on 2025-02-01.
//

#include "instruction_gen.h"

int VirtualRegister::count = 0;

std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Program> p) {
    for (auto d : p->decls){
        d->accept(*this);
    }

    return NO_REGISTER;
}

std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<FuncDecl> f) {
    emit_label(f->name, true);

    return NO_REGISTER;
}

std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Block> b) {
    for (auto s : b->stmts){
        s->accept(*this);
    }

    return NO_REGISTER;
}

std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<VarDecl> v) {
    if (v->is_local){
        symbol_table[v] = getRegister();
    }

    return NO_REGISTER;
}

std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Primary> p) {

    std::shared_ptr<VirtualRegister> r;

    switch (p->token->token_type) {
        case TT::INT_LITERAL:
        case TT::CHAR_LITERAL:
            r = getRegister();
            emit("mov", r, p->token->value);
            break;
        case TT::IDENTIFIER: {
            r = symbol_table[std::dynamic_pointer_cast<VarDecl>(p->symbol->decl)];
            break;
        }
        default:
            break;
    }

    return r;
}

std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Return> r) {

    if (r->expr.has_value()){
        std::shared_ptr<VirtualRegister> v = r->expr->get()->accept(*this);
        emit_branch("ret", v);
        return NO_REGISTER;
    }
    emit_branch("ret", "");

    return NO_REGISTER;
}

std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Binary> b) {

}

std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<If> ifStmt) {

}
std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<While> whileStmt) {

}
std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Break> breakStmt) {

}
std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Continue> continueStmt) {

}

std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Subscript> subscript) {

}
std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Member> member) {

}
std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Call> call) {

}
std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Unary> unary) {

}
std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<TypeCast> typeCast) {

}

std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<Type> type) {

}
std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<FunProto> funProto) {

}
std::shared_ptr<VirtualRegister> InstructionGen::visit(std::shared_ptr<StructDecl> structDecl) {

}

void InstructionGen::emit(std::string opcode, std::shared_ptr<VirtualRegister> r1, std::shared_ptr<VirtualRegister> r2){
    std::vector<std::shared_ptr<VirtualRegister>> r = {r1,r2};
    std::shared_ptr<Instruction> i = std::make_shared<Instruction>(opcode, r);
    instructions.push_back(i);
}
void InstructionGen::emit(std::string opcode, std::shared_ptr<VirtualRegister> r1){
    std::vector<std::shared_ptr<VirtualRegister>> r = {r1};
    std::shared_ptr<Instruction> i = std::make_shared<Instruction>(opcode, r);
    instructions.push_back(i);
}

void InstructionGen::emit(std::string opcode, std::shared_ptr<VirtualRegister> r1, std::string value){
    std::vector<std::shared_ptr<VirtualRegister>> r = {r1};
    std::shared_ptr<Instruction> i = std::make_shared<Instruction>(opcode, r, value);
    instructions.push_back(i);
}

void InstructionGen::emit(std::string opcode){
    std::vector<std::shared_ptr<VirtualRegister>> r;
    std::shared_ptr<Instruction> i = std::make_shared<Instruction>(opcode, r);
    instructions.push_back(i);
}

void InstructionGen::emit_branch(std::string opcode, std::string label) {
    std::shared_ptr<BranchInstruction> i = std::make_shared<BranchInstruction>(opcode, label);
    instructions.push_back(i);
}

void InstructionGen::emit_branch(std::string opcode, std::shared_ptr<VirtualRegister> r1) {
    std::vector<std::shared_ptr<VirtualRegister>> r = {r1};
    std::shared_ptr<BranchInstruction> i = std::make_shared<BranchInstruction>(opcode, r);
    instructions.push_back(i);
}

void InstructionGen::emit_label(std::string label, bool isFunc) {
    std::shared_ptr<Label> i = std::make_shared<Label>(label, isFunc);
    instructions.push_back(i);
}

std::shared_ptr<VirtualRegister> InstructionGen::getRegister(){
    return std::make_shared<VirtualRegister>();
}

std::string InstructionGen::getLabel(std::string name) {
    return name + std::to_string(label_id++);
}
