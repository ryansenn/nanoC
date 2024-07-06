/*
Semantic error: Type mismatch in function 'f' call, argument 'a' expected type 'int[5]' but received 'int[10]' at line 14 column 6
*/

void f(int a[5]){
    return;
}

int main(){
    int a[5];
    int b[10];

    f(a);
    f(b);
    return 0;
}