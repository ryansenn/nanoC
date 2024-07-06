/*
Semantic error: Incompatible types when initializing type 'char' using type 'int' at line 15 column 8
*/

int f(int a){
    return a;
}

int main(){

    int a;
    a=f(1);

    char b;
    b = f(a);

    return 0;
}