/*
Semantic error: Invalid unary type 'char' but expected type 'int' at line 8 column 6
*/
int main(){
    int a;
    !a;
    char b;
    !b;
    return 0;
}