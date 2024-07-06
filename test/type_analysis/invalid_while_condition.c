/*
Semantic error: While condition must be an integer at line 14 column 10
*/

int main(){

    int a;
    a=0;

    while(a < 5){
        a = a+1;
    }

    while('a'){
        a = a+1;
    }

    return 0;
}