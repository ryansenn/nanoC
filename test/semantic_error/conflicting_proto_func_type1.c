/*
Semantic error: Conflicting return type in function 'f' at line 7 column 4
*/

void f(int a, char b);

int f(int a, char b){
    return 1;
}

int main(){
    return 0;
}