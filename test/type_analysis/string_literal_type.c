/*
Semantic error: Type mismatch in function 'f' call, argument 'a' expected type 'char*' but received 'char' at line 12 column 6
*/

void f(char* a){
    return;
}

int main(){
    f("hello");
    f("bro");
    f('a');
    return 0;
}