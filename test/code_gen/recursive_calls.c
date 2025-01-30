/*
0
5
55
6765
*/
#include <print>

int fibonnaci(int n){
    if (n == 0){
        return 0;
    }
    if (n == 1){
        return 1;
    }

    return fibonnaci(n-1) + fibonnaci(n-2);
}

void p(int n){
    print_i(n);
    print_c('\n');
}

int main(){


    p(fibonnaci(0)); // 0
    p(fibonnaci(5)); // 5
    p(fibonnaci(10)); // 55
    p(fibonnaci(20)); // 6765


    return 0;
}