/*
12b1
*/

#include <print>

struct A {
    int i1;
    char a1;
    int i2;
    int* p;
};

struct B {
    struct A* p;
};

int main(){
    struct A a;
    a.i1 = 1;
    a.i2 = 2;
    a.a1 = 'b';
    a.p = &a.i1;

    //print_i(a.i1);
    //print_i(a.i2);
    //print_c(a.a1);
    //print_i(*a.p);

    struct B b;
    b.p = &a;

    print_i((*b.p).a2);

    return 0;
}