/*
7
6
10
-2
1
111110
1001
*/
#include <print>

int main(){

    print_i(1+6);
    print_c('\n');

    print_i(9 - 3);
    print_c('\n');

    print_i(2 * 5);
    print_c('\n');

    print_i(-5 / 2);
    print_c('\n');

    print_i(5 % 2);
    print_c('\n');

    print_i(1 < 2);
    print_i(2 > 1);
    print_i(1 >= 1);
    print_i(1 <= 1);
    print_i(1 == 1);
    print_i(1 != 1);

    print_c('\n');

    print_i(1 || 0);
    print_i(0 || 0);
    print_i(1 && 0);
    print_i(1 && 1);

    return 0;
}