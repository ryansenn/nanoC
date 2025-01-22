/*
13579
*/
#include <print>


int main(){

    int a;
    a = 0;

    while (a < 10){
        a = a + 1;
        if (a % 2 == 0){
            continue;
        }
        print_i(a);
    }


    return 0;
}