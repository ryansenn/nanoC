/*
Semantic error: Cannot reference non-lvalue expression at line 15 column 11
*/

struct S {
    int arr[10][10];
};

int main(){
    struct S s;
    struct S* p;
    p = &s;
    int* p2;
    p2 = &(s.arr[1][1]);
    p2 = &(1+1);

    return 0;
}