/*
Semantic error: Recursive reference 's' without a pointer in struct 'S' at line 9 column 11
*/

struct S {
    int a;
    struct S* sp;
    char b;
    struct S s;
};

int main(){
    return 0;
}