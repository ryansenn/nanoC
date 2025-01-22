/*
11
*/
#include <print>


int main(){

    int a;
    a = 0;

    while (1){
        if (a > 10){
            break;
        }
        a = a + 1;
    }

    print_i(a);

    return 0;
}