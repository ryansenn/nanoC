## C compiler

This is a compiler for a subset of C I built from scratch, targets x86 assembly.

### Supports:

-variables, functions, structs, pointers, arrays  
-control flow (if, while, break, continue)  
-expressions, function calls, returns  
-binary/unary operations (arithmetic, relational, logical)  
-standard types (int, char, void)

### Implements:
Lexing, recursive descent parsing, name/type analysis, register allocation and x86 assembly

### Future goals:
-(Current) Control flow graph, liveness analysis and optimized register allocation  
-Support dynamic memory with malloc/free  
-Support basic OOP


### Running compiler:

    ./compiler <file.c>


Options:  
&emsp;-lexer (print lexer tokens)  
&emsp;-ast (print abstract syntax tree)

---

### Example fibonacci program:

```
#include <print>

int fibonnaci(int n){
    if (n == 0){
        return 0;
    }
    if (n == 1){
        return 1;
    }
    return fibonnaci(n-1) + fibonnaci(n-2);
}

int main(){
    print_i(fibonnaci(20)); // 6765
    return 0;
}
```

AST:

```
Program (
    FuncDecl fibonnaci(VarDecl(int)) (int) (
        If ((n == 0)) (
            return( 0 )
        )
        If ((n == 1)) (
            return( 1 )
        )
        return( (Func Call fibonnaci ((n - 1) ) + Func Call fibonnaci ((n - 2) )) )
    )
    FuncDecl main() (int) (
        Func Call print_i (Func Call fibonnaci (20 ) )
        return( 0 )
    )
)
````

Generated IR:

```
fibonnaci:
    push rbp
    mov rbp, rsp
    mov %2, rdi
    mov %3, 0
    mov %4, %2
    cmp %4, %3
    sete %4
    movzx %4, %4
    cmp %4, 1
    jne end3
    mov %5, 0
    mov rax, %5
    jmp ret2
end3:
    mov %6, 1
    mov %7, %2
    cmp %7, %6
    sete %7
    movzx %7, %7
    cmp %7, 1
    jne end4
    mov %8, 1
    mov rax, %8
    jmp ret2
end4:
    mov %9, 1
    mov %10, %2
    sub %10, %9
    mov rdi, %10
    call fibonnaci
    mov %11, rax
    mov %12, 2
    mov %13, %2
    sub %13, %12
    mov rdi, %13
    call fibonnaci
    mov %14, rax
    mov %15, %11
    add %15, %14
    mov rax, %15
    jmp ret2
ret2:
    mov rsp, rbp
    pop rbp
    ret

main:
    push rbp
    mov rbp, rsp
    mov %16, 20
    mov rdi, %16
    call fibonnaci
    mov %17, rax
    mov rdi, %17
    call print_i
    mov %18, rax
    mov %19, 0
    mov rax, %19
    jmp ret5
ret5:
    mov rsp, rbp
    pop rbp
    ret
```
