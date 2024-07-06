/*
Semantic error: Recursive reference 'arr' without a pointer in struct 'S' at line 9 column 11
*/

struct S {
    int a;
    struct S* s;
    char b;
    struct S arr[10];
};

int main(){
    return 0;
}