/*
7
21
*/
#include <print>

int main(){
    int a;
    a = 0;

    int i;
    i = 0;

    while (i < 7){
        a = a + i;
        i = i + 1;
    }

    print_i(i);
    print_c('\n');
    print_i(a);

    return 0;
}