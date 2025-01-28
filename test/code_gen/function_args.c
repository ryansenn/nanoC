/*
1234abc
*/

#include <print>

struct A {
    int i1;
    int i2;
};

void f(char c1, struct A a1, struct A a2, char c2, char c3){
    print_i(a1.i1);
    print_i(a1.i2);
    print_i(a2.i1);
    print_i(a2.i2);
    print_c(c1);
    print_c(c2);
    print_c(c3);
    print_c('\n');
}

int main(){

    struct A a1;
    struct A a2;
    a1.i1 = 1;
    a1.i2 = 2;
    a2.i1 = 3;
    a2.i2 = 4;

    f('a', a1,a2, 'b', 'c');

    return 0;
}