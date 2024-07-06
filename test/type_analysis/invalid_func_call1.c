/*
Semantic error: Type mismatch in function 'f' call, argument 'b' expected type 'char' but received 'int' at line 11 column 6
*/

void f(int a, char b){
    return;
}

int main(){
    f(1,'m');
    f(1, 2);

    return 0;
}