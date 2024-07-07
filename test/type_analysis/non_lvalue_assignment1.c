/*
Semantic error: lvalue required as left operand of assignment at line 20 column 9
*/

struct S{int a;};

int main(){
    int i;
    int* p;

    i  = 0;
    *p = i;
    p  = &i;

    struct S s;
    s.a = 1;
    struct S arr[5];
    arr[1].a = 2;

    i+2=3;

    return 0;
}