/*
Semantic error: Type struct 'A' is not declared at line 9 column 11
*/

struct S{};

int main(){
    struct S s;
    struct A m;
    return 0;
}