/*
Semantic error: Too few/many arguments in function 'f' call at line 11 column 6
*/

void f(int a, int b){
    return;
}

int main(){
    f(1,2);
    f(1,2,3);

    return 0;
}