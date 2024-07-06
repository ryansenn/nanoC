/*
Semantic error: Incompatible types when initializing type 'int' using type 'void' at line 14 column 8
*/

void f(int a){
    return;
}

int main(){

    f(1);

    int a;
    a = f(1);

    return 0;
}