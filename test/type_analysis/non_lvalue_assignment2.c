/*
Semantic error: lvalue required as left operand of assignment at line 17 column 12
*/

struct S2{int a;};
struct S1{struct S2 s2;};

struct S2 f(){
    struct S2 s;
    return s;
}

int main(){

    struct S1 s1;
    s1.s2.a = 1;
    f().a = 1;

    return 0;
}