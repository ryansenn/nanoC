//
// Created by Ryan Senoune on 2024-07-08.
//

#include "code_gen.h"

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Program> p) {
    asmContext->emit("section .text");
    asmContext->emit("global start");
    for (const auto d : p->decls){
        d->accept(*this);
    }
    asmContext->emit("start:");
    asmContext->emit("call main");
    asmContext->emit("mov rdi, rax");
    asmContext->emit("mov rax, 0x2000001");
    asmContext->emit("syscall");

    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<FuncDecl> f) {
    if (f->name == "emit_asm"){
        return NO_REGISTER;
    }

    asmContext->emit(f->name + ":");
    asmContext->emit("push rbp");
    asmContext->emit("mov rbp, rsp");

    returnLabel = asmContext->getLabel("return");

    f->block->accept(*this);

    asmContext->emit(returnLabel + ":");
    asmContext->emit("mov rsp, rbp");
    asmContext->emit("pop rbp");
    asmContext->emit("ret");

    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Block> b) {

    if (b->offset)
        asmContext->emit("sub rsp, " + std::to_string(b->offset));

    for (auto s : b->stmts){
        s->accept(*this);
    }

    if (b->offset)
        asmContext->emit("add rsp, " + std::to_string(b->offset));

    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Primary> p){
    std::shared_ptr<Register> r = asmContext->getRegister();

    switch (p->token->token_type) {
        case TT::INT_LITERAL:
        case TT::CHAR_LITERAL:
            asmContext->emit("mov " + r->name + ", " + p->token->value);
            break;
        case TT::IDENTIFIER: {
            std::shared_ptr<VarDecl> v = std::dynamic_pointer_cast<VarDecl>(p->symbol->decl);
            asmContext->emit("mov " + r->name + ", " + v->getAddress());
            break;
        }
        default:
            break;
    }

    return r;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Call> c){
    std::shared_ptr<Register> r = NO_REGISTER;

    if (c->identifier->value == "emit_asm"){
        std::string instruction = std::dynamic_pointer_cast<Primary>(c->args[0])->token->value;
        asmContext->emit(instruction);
        return r;
    }

    std::shared_ptr<FuncDecl> f = std::dynamic_pointer_cast<FuncDecl>(c->symbol->decl);

    if (f->type->token->token_type != TT::VOID){
        r = asmContext->reg_map["rax"];
    }

    for (std::shared_ptr<Expr> e : c->args){
        asmContext->emit("push " + e->accept(*this)->name);
    }

    asmContext->emit("call " + c->identifier->value);
    asmContext->emit("add rsp, " + std::to_string(f->arg_offset));

    return r;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Binary> b){


    if (b->op->token_type == TT::ASSIGN){
        std::string a1 = b->expr1->accept(*addrGen);
        std::shared_ptr<Register> r2 = b->expr2->accept(*this);
        asmContext->emit("mov " + a1 + ", " + r2->name);
        return r2;
    }

    std::shared_ptr<Register> r1 = b->expr1->accept(*this);
    std::shared_ptr<Register> r2 = b->expr2->accept(*this);

    switch (b->op->token_type) {
        case TT::PLUS:
            asmContext->emit("add " + r1->name + ", " + r2->name);
            break;
        case TT::MINUS:
            asmContext->emit("sub " + r1->name + ", " + r2->name);
            break;
        case TT::ASTERISK:
            asmContext->emit("imul " + r1->name + ", " + r2->name);
            break;
        case TT::DIV:
            asmContext->emit("mov rax, " + r1->name);
            asmContext->emit("cqo");
            asmContext->emit("idiv " + r2->name);
            return asmContext->reg_map["rax"];
        case TT::REM:
            asmContext->emit("mov rax, " + r1->name);
            asmContext->emit("cqo");
            asmContext->emit("idiv " + r2->name);
            return asmContext->reg_map["rdx"];
        case TT::LE:
            asmContext->emit("cmp " + r1->name + ", " + r2->name);
            asmContext->emit("setle " + r1->name_b);
            asmContext->emit("movzx " + r1->name + ", " + r1->name_b);
            break;
        case TT::LT:
            asmContext->emit("cmp " + r1->name + ", " + r2->name);
            asmContext->emit("setl " + r1->name_b);
            asmContext->emit("movzx " + r1->name + ", " + r1->name_b);
            break;
        case TT::GE:
            asmContext->emit("cmp " + r1->name + ", " + r2->name);
            asmContext->emit("setge " + r1->name_b);
            asmContext->emit("movzx " + r1->name + ", " + r1->name_b);
            break;
        case TT::GT:
            asmContext->emit("cmp " + r1->name + ", " + r2->name);
            asmContext->emit("setg " + r1->name_b);
            asmContext->emit("movzx " + r1->name + ", " + r1->name_b);
            break;
        case TT::EQ:
            asmContext->emit("cmp " + r1->name + ", " + r2->name);
            asmContext->emit("sete " + r1->name_b);
            asmContext->emit("movzx " + r1->name + ", " + r1->name_b);
            break;
        case TT::NE:
            asmContext->emit("cmp " + r1->name + ", " + r2->name);
            asmContext->emit("setne " + r1->name_b);
            asmContext->emit("movzx " + r1->name + ", " + r1->name_b);
            break;
        case TT::LOGOR:
            asmContext->emit("or " + r1->name + ", " + r2->name);
            break;
        case TT::LOGAND:
            asmContext->emit("and " + r1->name + ", " + r2->name);
            break;
        default:
            break;
    }

    asmContext->freeRegister(r2);

    return r1;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Unary> u){

    if (u->op->token_type == TT::AND){
        std::string a = u->expr1->accept(*addrGen);
        std::shared_ptr<Register> r = asmContext->getRegister();
        asmContext->emit("lea " + r->name + ", " + a);
        return r;
    }

    std::shared_ptr<Register> r = u->expr1->accept(*this);

    switch (u->op->token_type) {
        case TT::MINUS:
            asmContext->emit("neg " + r->name);
            break;
        case TT::NOT:
            asmContext->emit("test " + r->name + ", " + r->name);
            asmContext->emit("sete " + r->name_b);
            asmContext->emit("movzx " + r->name + ", " + r->name_b);
            break;
        case TT::ASTERISK:
            asmContext->emit("mov " + r->name + ", [" + r->name + "]");
            break;
        default:
            break;
    }

    return r;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<If> f) {

    if (f->stmt2.has_value()){
        std::string else_label = asmContext->getLabel("else");
        std::string end = asmContext->getLabel("end");

        std::shared_ptr<Register> r = f->expr1->accept(*this);
        asmContext->emit("cmp " + r->name + ", 1");
        asmContext->emit("jne " + else_label);

        f->stmt1->accept(*this);
        asmContext->emit("jmp " + end);

        asmContext->emit(else_label+":");
        f->stmt2->get()->accept(*this);

        asmContext->emit(end+":");
    }
    else{
        std::string end = asmContext->getLabel("end");

        std::shared_ptr<Register> r = f->expr1->accept(*this);
        asmContext->emit("cmp " + r->name + ", 1");
        asmContext->emit("jne " + end);
        f->stmt1->accept(*this);
        asmContext->emit(end+":");
    }


    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<While> w){

    std::string start = asmContext->getLabel("while");
    std::string end = asmContext->getLabel("end");

    loopLabels.push_back(std::make_pair(start,end));

    asmContext->emit(start+":");
    std::shared_ptr<Register> r = w->expr->accept(*this);
    asmContext->emit("cmp " + r->name + ", 1");
    asmContext->emit("jne " + end);

    w->stmt->accept(*this);

    asmContext->emit("jmp " + start);
    asmContext->emit(end+":");

    loopLabels.pop_back();

    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Subscript>){
    return NULL;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Member>){
    return NULL;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<TypeCast>){
    return NULL;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Return> f) {
    if (f->expr.has_value()){
        std::shared_ptr<Register> r = f->expr->get()->accept(*this);
        asmContext->emit("mov rax, " + r->name);
        asmContext->freeRegister(r);
    }

    asmContext->emit("jmp " + returnLabel);

    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Break>){

    asmContext->emit("jmp " + loopLabels.back().second);

    return NO_REGISTER;
}
std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Continue>){

    asmContext->emit("jmp " + loopLabels.back().first);

    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<FunProto>){
    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<VarDecl> v){
    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<StructDecl>){
    return NO_REGISTER;
}

std::shared_ptr<Register> CodeGen::visit(std::shared_ptr<Type>){
    return NO_REGISTER;
}