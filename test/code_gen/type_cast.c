/*
97100
*/

#include <print>

int main() {
    char c;
    c = 'a';
    int i;
    i = (int)c;
    print_i(i);

    int x;
    x = 100;
    int *p1;
    p1 = &x;
    void *vp;
    vp = (void *)p1;
    int *p2;
    p2 = (int *)vp;
    print_i(*p2);

    return 0;
}
