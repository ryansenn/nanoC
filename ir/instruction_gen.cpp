//
// Created by Ryan Senoune on 2025-02-01.
//

#include "instruction_gen.h"

int VirtualRegister::count = 0;
std::vector<std::shared_ptr<Register>> Register::registers = {
        // General-purpose registers for temporary use
        std::make_shared<Register>("r10", "r10d", "r10w", "r10b"),
        std::make_shared<Register>("r11", "r11d", "r11w", "r11b"),
        std::make_shared<Register>("r12", "r12d", "r12w", "r12b"),
        std::make_shared<Register>("r13", "r13d", "r13w", "r13b"),

        // Return value register (rax)
        std::make_shared<Register>("rax", "eax", "ax", "al"),

        // Stack and base pointer registers
        std::make_shared<Register>("rbp", "ebp", "bp", "bpl"),  // Base pointer
        std::make_shared<Register>("rsp", "esp", "sp", "spl"),   // Stack pointer

        // Argument-passing registers (in order)
        std::make_shared<Register>("rdi", "edi", "di", "dil"),  // 1st argument
        std::make_shared<Register>("rsi", "esi", "si", "sil"),  // 2nd argument
        std::make_shared<Register>("rdx", "edx", "dx", "dl"),   // 3rd argument
        std::make_shared<Register>("rcx", "ecx", "cx", "cl"),   // 4th argument
        std::make_shared<Register>("r8", "r8d", "r8w", "r8b"),  // 5th argument
        std::make_shared<Register>("r9", "r9d", "r9w", "r9b"),  // 6th argument
};

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Program> p) {
    for (auto d : p->decls){
        d->accept(*this);
    }

    return NO_REGISTER;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<FuncDecl> f) {
    if (f->name == "emit_asm"){
        return NO_REGISTER;
    }

    emit_label(f->name, true);

    emit("push", Register::get_physical_register("rbp"));
    emit("mov", Register::get_physical_register("rbp"),Register::get_physical_register("rsp"));

    for (int i = 0; i<std::min(f->args.size(), static_cast<size_t>(6));i++) {
        f->args[i]->accept(*this);
        auto arg = symbol_table[f->args[i]];
        emit("mov", arg,Register::get_physical_register(arg_reg_order[i]));
    }

    int offset = 16;

    for (int i = 6; i < f->args.size();i++){
        f->args[i]->accept(*this);
        emit("mov", symbol_table[f->args[i]], "[rbp + " + std::to_string(offset) + "]");
        offset += 8;
    }

    return_label = gen_label("ret");

    f->block->accept(*this);

    emit_label(return_label, false);
    emit("mov", Register::get_physical_register("rsp"), Register::get_physical_register("rbp"));
    emit("pop", Register::get_physical_register("rbp"));
    emit_branch("ret","");

    return NO_REGISTER;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Call> c) {
    if (c->identifier->value == "emit_asm"){
        emit("emit_asm", Register::get_physical_register("rax"),std::dynamic_pointer_cast<Primary>(c->args[0])->token->value);
        return NO_REGISTER;
    }

    for (int i = 0; i<std::min(c->args.size(), static_cast<size_t>(6));i++) {
        auto arg = c->args[i]->accept(*this);
        emit("mov", Register::get_physical_register(arg_reg_order[i]), arg);
    }

    int stack_size = 0;

    for (int i = c->args.size()-1; i >= 6;i--){
        emit("push", c->args[i]->accept(*this));
        stack_size += 8;
    }

    emit_branch("call", c->identifier->value);

    if (stack_size)
        emit("add", Register::get_physical_register("rsp"), std::to_string(stack_size));

    return Register::get_physical_register("rax");
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Block> b) {
    for (auto s : b->stmts){
        s->accept(*this);
    }

    return NO_REGISTER;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<VarDecl> v) {
    if (v->is_local){
        symbol_table[v] = gen_register();

        if (v->type->token->token_type == TT::STRUCT){
            emit("sub", Register::get_physical_register("rsp"), std::to_string(std::dynamic_pointer_cast<StructDecl>(v->type->symbol->decl)->size));
            emit("mov", symbol_table[v], Register::get_physical_register("rsp"));
        }
    }

    return NO_REGISTER;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Primary> p) {

    std::shared_ptr<VirtualRegister> r;

    switch (p->token->token_type) {
        case TT::INT_LITERAL:
        case TT::CHAR_LITERAL:
            r = gen_register();
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

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Return> r) {

    if (r->expr.has_value()){
        std::shared_ptr<Register> v = r->expr->get()->accept(*this);
        emit("mov", Register::get_physical_register("rax"), v);
    }

    emit_branch("jmp", return_label);
    return NO_REGISTER;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Binary> b) {

    if (b->op->token_type == TT::ASSIGN){
        std::shared_ptr<Register> r1 = get_address(b->expr1);
        std::shared_ptr<Register> r2 = b->expr2->accept(*this);
        emit("mov", r1->mem(), r2);
        return r2;
    }

    std::shared_ptr<Register> r1 = b->expr1->accept(*this);
    std::shared_ptr<Register> r2 = b->expr2->accept(*this);
    std::shared_ptr<Register> res = gen_register();

    emit("mov", res, r1);

    switch (b->op->token_type) {
        case TT::PLUS:
            emit("add", res, r2);
            break;
        case TT::MINUS:
            emit("sub", res, r2);
            break;
        case TT::ASTERISK:
            emit("imul", res, r2);
            break;
        case TT::DIV:
            emit("mov", Register::get_physical_register("rax"), res);
            emit("cqo");
            emit("idiv", r2);
            emit("mov", res, Register::get_physical_register("rax"));
            break;
        case TT::REM:
            emit("mov", Register::get_physical_register("rax"), res);
            emit("cqo");
            emit("idiv", r2);
            emit("mov", res, Register::get_physical_register("rdx"));
            break;
        case TT::LE:
            emit("cmp", res, r2);
            emit("setle", res->copy(1));
            emit("movzx", res, res->copy(1));
            break;
        case TT::LT:
            emit("cmp", res, r2);
            emit("setl", res->copy(1));
            emit("movzx", res, res->copy(1));
            break;
        case TT::GE:
            emit("cmp", res, r2);
            emit("setge", res->copy(1));
            emit("movzx", res, res->copy(1));
            break;
        case TT::GT:
            emit("cmp", res, r2);
            emit("setg", res->copy(1));
            emit("movzx", res, res->copy(1));
            break;
        case TT::EQ:
            emit("cmp", res, r2);
            emit("sete", res->copy(1));
            emit("movzx", res, res->copy(1));
            break;
        case TT::NE:
            emit("cmp", res, r2);
            emit("setne", res->copy(1));
            emit("movzx", res, res->copy(1));
            break;
        case TT::LOGOR:
            emit("or", res, r2);
            break;
        case TT::LOGAND:
            emit("and", res, r2);
            break;
        default:
            break;
    }

    return res;


}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Unary> u) {
    if (u->op->token_type == TT::AND){
        return get_address(u->expr1);
    }

    std::shared_ptr<Register> r = u->expr1->accept(*this);
    std::shared_ptr<Register> res = gen_register();

    emit("mov", res, r);

    switch (u->op->token_type) {
        case TT::MINUS:
            emit("neg ", res);
            break;
        case TT::NOT:
            emit("test", res, res);
            emit("sete", res->copy(1));
            emit("movzx", res, res->copy(1));
            break;
        case TT::ASTERISK:
            if (u->expr1->type->token->token_type == TT::STRUCT){
                return res;
            }
            emit("mov ", res, res->mem());
            break;
        default:
            break;
    }

    return res;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<If> f) {
    if (f->stmt2.has_value()){
        std::string else_label = gen_label("else");
        std::string end = gen_label("end");

        std::shared_ptr<Register> r = f->expr1->accept(*this);
        emit("cmp", r,"1");
        emit_branch("jne", else_label);

        f->stmt1->accept(*this);
        emit_branch("jmp", end);

        emit_label(else_label, false);
        f->stmt2->get()->accept(*this);

        emit_label(end, false);
    }
    else{
        std::string end = gen_label("end");

        std::shared_ptr<Register> r = f->expr1->accept(*this);
        emit("cmp", r, "1");
        emit_branch("jne ", end);
        f->stmt1->accept(*this);
        emit_label(end, false);
    }

    return NO_REGISTER;
}
std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<While> w) {
    std::string start = gen_label("while");
    std::string end = gen_label("end");

    loop_labels.push_back(std::make_pair(start, end));

    emit_label(start, false);

    std::shared_ptr<Register> r = w->expr->accept(*this);
    emit("cmp", r, "1");
    emit_branch("jne", end);

    w->stmt->accept(*this);

    emit_branch("jmp", start);
    emit_label(end, false);

    loop_labels.pop_back();

    return NO_REGISTER;

}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Break> b) {
    emit_branch("jmp", loop_labels.back().second);
    return NO_REGISTER;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Continue>) {
    emit_branch("jmp", loop_labels.back().first);
    return NO_REGISTER;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Member> m) {
    std::shared_ptr<VirtualRegister> res = gen_register();
    emit("mov", res, get_address(m)->mem());

    return res;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Subscript> subscript) {
    return NO_REGISTER;
}

void InstructionGen::emit(std::string opcode, std::shared_ptr<Register> r1, std::shared_ptr<Register> r2){
    std::vector<std::shared_ptr<Register>> r = {r1,r2};
    std::shared_ptr<Instruction> i = std::make_shared<BasicInstruction>(opcode, r);
    instructions.push_back(i);
}
void InstructionGen::emit(std::string opcode, std::shared_ptr<Register> r1){
    std::vector<std::shared_ptr<Register>> r = {r1};
    std::shared_ptr<Instruction> i = std::make_shared<BasicInstruction>(opcode, r);
    instructions.push_back(i);
}

void InstructionGen::emit(std::string opcode, std::shared_ptr<Register> r1, std::string value){
    std::vector<std::shared_ptr<Register>> r = {r1};
    std::shared_ptr<Instruction> i = std::make_shared<BasicInstruction>(opcode, r, value);
    instructions.push_back(i);
}

void InstructionGen::emit(std::string opcode){
    std::vector<std::shared_ptr<Register>> r;
    std::shared_ptr<Instruction> i = std::make_shared<BasicInstruction>(opcode, r);
    instructions.push_back(i);
}

void InstructionGen::emit_branch(std::string opcode, std::string label) {
    std::shared_ptr<BranchInstruction> i = std::make_shared<BranchInstruction>(opcode, label);
    instructions.push_back(i);
}

void InstructionGen::emit_branch(std::string opcode, std::shared_ptr<Register> r1) {
    std::vector<std::shared_ptr<Register>> r = {r1};
    std::shared_ptr<BranchInstruction> i = std::make_shared<BranchInstruction>(opcode, r);
    instructions.push_back(i);
}

void InstructionGen::emit_label(std::string label, bool isFunc) {
    std::shared_ptr<Label> i = std::make_shared<Label>(label, isFunc);
    instructions.push_back(i);
}

std::shared_ptr<VirtualRegister> InstructionGen::gen_register(){
    return std::make_shared<VirtualRegister>();
}

std::string InstructionGen::gen_label(std::string name) {
    return name + std::to_string(label_id++);
}

std::shared_ptr<Register> InstructionGen::get_address(std::shared_ptr<Expr> e) {
    if (auto p = std::dynamic_pointer_cast<Primary>(e)) {
        // this should only be for identifiers
        return symbol_table[std::dynamic_pointer_cast<VarDecl>(p->symbol->decl)];
    }
    else if (auto s = std::dynamic_pointer_cast<Subscript>(e)) {
        std::shared_ptr<Register> base = get_address(s->array);
        std::shared_ptr<Register> index = s->index->accept(*this);
        std::shared_ptr<Register> res = gen_register();
        emit("mov", res, base);
        emit("imul", index, std::to_string(s->type->size));
        emit("add", res, index);
        return res;
    }
    else if (auto m = std::dynamic_pointer_cast<Member>(e)) {
        std::shared_ptr<Register> base = get_address(m->structure);
        std::shared_ptr<VirtualRegister> res = gen_register();
        emit("mov", res, base);
        emit("add", res, std::to_string(std::dynamic_pointer_cast<VarDecl>(m->symbol->decl)->offset));
        return res;
    }
    else if (auto u = std::dynamic_pointer_cast<Unary>(e)) {
        if(u->op->token_type == TT::ASTERISK) {
            return u->expr1->accept(*this);
        }
    }

    return nullptr;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<TypeCast> typeCast) {
    return NO_REGISTER;
}

std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<Type> type) {
    return NO_REGISTER;
}
std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<FunProto> funProto) {
    return NO_REGISTER;
}
std::shared_ptr<Register> InstructionGen::visit(std::shared_ptr<StructDecl> structDecl) {
    return NO_REGISTER;
}