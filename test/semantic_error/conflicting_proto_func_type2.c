/*
Semantic error: Conflicting type in argument 'b' in function 'f' at line 7 column 5
*/

void f(int a, char b);

void f(int a, int b){
    return;
}

int main(){
    return 0;
}