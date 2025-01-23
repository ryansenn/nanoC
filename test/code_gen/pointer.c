/*
5
*/
#include <print>

int main(){
    int a;
    a = 5;
    int* p;
    p = &a;
    int b;
    b = *p;
    print_i(b);
    return 0;
}