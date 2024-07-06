/*
Semantic error: Struct 'S' has no member named 'hello' at line 12 column 7
*/

struct S {
    int a;
};

int main(){
    struct S s;
    s.a = 1;
    s.hello;

    return 0;
}