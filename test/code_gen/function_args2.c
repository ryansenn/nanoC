/*
23456789
1256
*/

#include <print>


void p(int a, int b, int c, int d, int e, int f, int g, int i){
    print_i(a);
    print_i(b);
    print_i(c);
    print_i(d);
    print_i(e);
    print_i(f);
    print_i(g);
    print_i(i);
    print_c('\n');
}

struct A {
    int i1;
    int i2;
};

void f(struct A a){
    a.i1 = 1;
    a.i2 = 2;
    print_i(a.i1);
    print_i(a.i2);
}

int main(){
    p(2,3,4,5,6,7,8,9);

    struct A a;
    a.i1 = 5;
    a.i2 = 6;

    f(a);

    print_i(a.i1);
    print_i(a.i2);

    return 0;
}