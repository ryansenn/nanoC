/*
Parsing error: Expected comma in between function call arguments at line 11 column 23 found Semicolon
*/

int f(int a, int b, int c){
    return 1;
}

int main() {
    int a;
    a = f(1,2+2,3/2*5;
}