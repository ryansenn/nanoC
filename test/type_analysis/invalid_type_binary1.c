/*
Semantic error: Invalid operand type for binary operator '<' at line 21 column 9
*/

struct S1{};
struct S2{};

int main(){
    int a;
    int b;

    a < b;
    a <= b;
    a == b;
    a + b;
    a = 1;

    struct S1 s1;
    struct S2 s2;

    s1 < s2;
    return 0;
}