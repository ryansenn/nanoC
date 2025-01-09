//
// Created by Ryan Senoune on 2024-05-21.
//

#ifndef COMPILER_AST_H
#define COMPILER_AST_H

#include <variant>
#include <vector>
#include <string>
#include <optional>
#include <sstream>
#include "../lexer/token.h"

template <typename T>
class Visitor{
public:
    virtual T visit(std::shared_ptr<class Program> program) = 0;
    virtual T visit(std::shared_ptr<class FuncDecl> func) = 0;
    virtual T visit(std::shared_ptr<class Block> block) = 0;
    virtual T visit(std::shared_ptr<class Return> ret) = 0;
    virtual T visit(std::shared_ptr<class If> block) = 0;
    virtual T visit(std::shared_ptr<class While> block) = 0;
    virtual T visit(std::shared_ptr<class Break> block) = 0;
    virtual T visit(std::shared_ptr<class Continue> block) = 0;
    virtual T visit(std::shared_ptr<class VarDecl> var) = 0;
    virtual T visit(std::shared_ptr<class Subscript> subscript) = 0;
    virtual T visit(std::shared_ptr<class Member> member) = 0;
    virtual T visit(std::shared_ptr<class Call> call) = 0;
    virtual T visit(std::shared_ptr<class Primary> primary) = 0;
    virtual T visit(std::shared_ptr<class Unary> unary) = 0;
    virtual T visit(std::shared_ptr<class TypeCast> typeCast) = 0;
    virtual T visit(std::shared_ptr<class Binary> binary) = 0;
    virtual T visit(std::shared_ptr<class Type> type) = 0;
    virtual T visit(std::shared_ptr<class FunProto> funProto) = 0;
    virtual T visit(std::shared_ptr<class StructDecl> funProto) = 0;
};

class Register;

struct Decl {
    Decl(){}
    virtual void accept(Visitor<void>& visitor) = 0;
    virtual std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor)=0;
};

struct Symbol  : std::enable_shared_from_this<Symbol>{
    enum class Type {VAR,FUNC,PROTO,STRUCT};
    Type type;

    std::shared_ptr<Decl> decl;

    Symbol(Type type, std::shared_ptr<Decl> decl) : type(type), decl(decl) {}
};


struct Type : std::enable_shared_from_this<Type> {
public:
    std::shared_ptr<Token> token; // Inside of token we find the type (Token.token_type)
    std::string name;
    int pointerCount;
    std::vector<int> arraySize;
    std::shared_ptr<Symbol> symbol;
    int size;

    Type(std::shared_ptr<Token> token) : token(std::move(token)), pointerCount(0), arraySize(0) {}

    bool operator==(const Type& t) const {
        return token->token_type == t.token->token_type && name == t.name && pointerCount == t.pointerCount && arraySize == t.arraySize;
    }

    bool operator!=(const Type& t) const {
        return !(*this == t);
    }

    std::string str();

    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }

    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

std::ostream& operator<<(std::ostream& os, const Type& type);

struct Stmt {
    virtual void accept(Visitor<void>& visitor) = 0;
    virtual std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor)=0;
};

struct Expr : Stmt{
public:
    std::shared_ptr<Type> type;
    bool lvalue = false;
    virtual void accept(Visitor<void>& visitor) = 0;
    virtual std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor)=0;
};


struct Subscript : Expr, std::enable_shared_from_this<Subscript> {
    std::shared_ptr<Expr> array;
    std::shared_ptr<Expr> index;
    std::shared_ptr<Token> token;
    Subscript(std::shared_ptr<Expr> array, std::shared_ptr<Expr> index, std::shared_ptr<Token> token) : array(std::move(array)), index(std::move(index)), token(std::move(token)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct Member : Expr, std::enable_shared_from_this<Member> {
    std::shared_ptr<Expr> structure;
    std::string member;
    std::shared_ptr<Token> token;
    Member(std::shared_ptr<Expr> structure, std::string member, std::shared_ptr<Token> token) : structure(std::move(structure)), member(member), token(std::move(token)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};


struct Primary : Expr, std::enable_shared_from_this<Primary> {
    // Inside of the token, we find the type (token.token_type) and value (token.value)
    std::shared_ptr<Token> token; // identifier, char, int
    std::shared_ptr<Symbol> symbol;
    Primary(std::shared_ptr<Token> token) : token(std::move(token)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct Call : Expr, std::enable_shared_from_this<Call> {
    std::shared_ptr<Token> identifier; // The operator is held into Token.value
    std::vector<std::shared_ptr<Expr>> args;
    std::shared_ptr<Symbol> symbol;
    Call(std::shared_ptr<Token> identifier) : identifier(std::move(identifier)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct Unary : Expr, std::enable_shared_from_this<Unary> {
    std::shared_ptr<Token> op; // The operator is held into Token.token_type
    std::shared_ptr<Expr> expr1;
    Unary(std::shared_ptr<Token> o, std::shared_ptr<Expr> e1) : op(std::move(o)), expr1(std::move(e1)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct TypeCast : Expr, std::enable_shared_from_this<TypeCast> {
    std::shared_ptr<Type> typeCast; // The operator is held into Token.token_type
    std::shared_ptr<Expr> expr1;
    TypeCast(std::shared_ptr<Type> typeCast, std::shared_ptr<Expr> expr1) : typeCast(std::move(typeCast)), expr1(std::move(expr1)){}

    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct Binary : Expr, std::enable_shared_from_this<Binary> {
    std::shared_ptr<Expr> expr1;
    std::shared_ptr<Token> op; // The operator is held into Token.token_type
    std::shared_ptr<Expr> expr2;
    Binary(std::shared_ptr<Expr> e1, std::shared_ptr<Token> o, std::shared_ptr<Expr> e2) : expr1(std::move(e1)), op(std::move(o)), expr2(std::move(e2)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct VarDecl : Decl, Stmt, std::enable_shared_from_this<VarDecl> {
    std::shared_ptr<Type> type;
    std::string name;
    int offset;
    VarDecl(std::shared_ptr<Type> t, std::string n) : name(n), type(std::move(t)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct StructDecl : Decl, std::enable_shared_from_this<StructDecl> {
    std::vector<std::shared_ptr<VarDecl>> varDecls;
    std::string name;
    int size = 8; // TO CHANGE NOT HARDCODE
    StructDecl(std::string& n) : name(n) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct Return : Stmt, std::enable_shared_from_this<Return> {
public:
    std::optional<std::shared_ptr<Expr>> expr;
    std::shared_ptr<Symbol> funcDecl;
    std::shared_ptr<Token> token;
    Return(std::shared_ptr<Token> token): token(std::move(token)) {}
    Return(std::shared_ptr<Expr> e, std::shared_ptr<Token> token) : expr(std::move(e)),token(std::move(token)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct If : Stmt, std::enable_shared_from_this<If> {
public:
    std::shared_ptr<Expr> expr1;
    std::shared_ptr<Stmt> stmt1;
    std::optional<std::shared_ptr<Stmt>> stmt2;
    std::shared_ptr<Token> token;
    If(std::shared_ptr<Expr> e1, std::shared_ptr<Stmt> s1, std::shared_ptr<Token> token) : expr1(std::move(e1)), stmt1(std::move(s1)), token(std::move(token)) {}
    If(std::shared_ptr<Expr> e1, std::shared_ptr<Stmt> s1, std::shared_ptr<Stmt> s2, std::shared_ptr<Token> token) : expr1(std::move(e1)), stmt1(std::move(s1)), stmt2(std::move(s2)), token(std::move(token)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct While : Stmt, std::enable_shared_from_this<While> {
public:
    std::shared_ptr<Expr> expr;
    std::shared_ptr<Stmt> stmt;
    std::shared_ptr<Token> token;
    While(std::shared_ptr<Expr> e, std::shared_ptr<Stmt> s, std::shared_ptr<Token> token) : expr(std::move(e)), stmt(std::move(s)), token(std::move(token)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct Block : Stmt, std::enable_shared_from_this<Block> {
    std::vector<std::shared_ptr<Stmt>> stmts;
    Block(std::vector<std::shared_ptr<Stmt>> s) : stmts(std::move(s)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct Continue : Stmt, std::enable_shared_from_this<Continue> {
    Continue() {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct Break : Stmt, std::enable_shared_from_this<Break> {
    Break() {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct FuncDecl : Decl, std::enable_shared_from_this<FuncDecl> {
    std::shared_ptr<Type> type;
    std::string name;
    std::vector<std::shared_ptr<VarDecl>> args;
    std::shared_ptr<Block> block;
    int offset;
    FuncDecl(std::shared_ptr<Type> t, std::string& n, std::vector<std::shared_ptr<VarDecl>> a, std::shared_ptr<Block> b) : name(n), type(std::move(t)), args(std::move(a)), block(std::move(b)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct FunProto : Decl, std::enable_shared_from_this<FunProto> {
    std::shared_ptr<Type> type;
    std::string name;
    std::vector<std::shared_ptr<VarDecl>> args;
    FunProto(std::shared_ptr<Type> t,std::string n, std::vector<std::shared_ptr<VarDecl>> a) : name(n), type(std::move(t)), args(std::move(a)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
};

struct Program : public std::enable_shared_from_this<Program>{
    std::vector<std::shared_ptr<Decl>> decls;
    Program(std::vector<std::shared_ptr<Decl>> d) : decls(std::move(d)) {}
    void accept(Visitor<void>& visitor){
        visitor.visit(shared_from_this());
    }
    std::shared_ptr<Register> accept(Visitor<std::shared_ptr<Register>>& visitor){
        return visitor.visit(shared_from_this());
    }
    void addStandardLibrary(){
        // Standard library functions
        std::shared_ptr<Type> voidType = std::make_shared<Type>(std::make_shared<Token>(TT::VOID));

        std::vector<std::shared_ptr<VarDecl>> intArg = {std::make_shared<VarDecl>(std::make_shared<Type>(std::make_shared<Token>(TT::INT)), "i")};
        std::shared_ptr<Decl> print_i = std::make_shared<FunProto>(voidType,"print_i",std::move(intArg));

        decls.insert(decls.begin(),print_i);
    }
};

class PrintVisitor : public Visitor<void>{

    std::string space = "    ";
    std::string indent = "";
    int w = 1;

    void incr();
    void decr();
    void visit(std::shared_ptr<Program> program) override;
    void visit(std::shared_ptr<FuncDecl> func) override;
    void visit(std::shared_ptr<FunProto> funProto) override;
    void visit(std::shared_ptr<Block> block) override;
    void visit(std::shared_ptr<If> i) override;
    void visit(std::shared_ptr<While> w) override;
    void visit(std::shared_ptr<Continue> c) override;
    void visit(std::shared_ptr<Break> b) override;
    void visit(std::shared_ptr<Return> ret) override;
    void visit(std::shared_ptr<VarDecl> varDecl) override;
    void visit(std::shared_ptr<Type> type) override;
    void visit(std::shared_ptr<Call> call) override;
    void visit(std::shared_ptr<StructDecl> structDecl) override;
    void visit(std::shared_ptr<Unary> unary) override;
    void visit(std::shared_ptr<TypeCast> typeCast) override;
    void visit(std::shared_ptr<Binary> binary) override;
    void visit(std::shared_ptr<Primary> primary) override;
    void visit(std::shared_ptr<Subscript> subscript) override;
    void visit(std::shared_ptr<Member> member) override;
};

#endif //COMPILER_AST_H
