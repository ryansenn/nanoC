/*
7
6
10
-2
1
111110
*/
#include <print>

int main(){
    int a;
    a = 1+6;
    print_i(a);
    print_c('\n');

    a = 9 - 3;
    print_i(a);
    print_c('\n');

    a = 2 * 5;
    print_i(a);
    print_c('\n');

    a = -5 / 2;
    print_i(a);
    print_c('\n');

    a = 5 % 2;
    print_i(a);
    print_c('\n');

    a = 1 < 2;
    print_i(a);

    a = 2 > 1;
    print_i(a);

    a = 1 >= 1;
    print_i(a);

    a = 1 <= 1;
    print_i(a);

    a = 1 == 1;
    print_i(a);

    a = 1 != 1;
    print_i(a);

    return 0;
}