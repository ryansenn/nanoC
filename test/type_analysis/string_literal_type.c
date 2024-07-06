/*
Semantic error: Type mismatch in function 'f' call, argument 'a' expected type 'char[6]' but received 'char[4]' at line 11 column 6
*/

void f(char a[6]){
    return;
}

int main(){
    f("hello");
    f("bro");
    return 0;
}