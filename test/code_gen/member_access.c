/*
12b
*/

#include <print>

struct A {
    int i1;
    char a1;
    int i2;
};

int main(){
    struct A a;
    a.i1 = 1;
    a.i2 = 2;
    a.a1 = 'b';

    print_i(a.i1);
    print_i(a.i2);
    print_c(a.a1);

    return 0;
}