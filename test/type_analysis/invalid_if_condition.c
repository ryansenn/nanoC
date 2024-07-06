/*
Semantic error: If condition expression must be an integer at line 22 column 7
*/

struct S{};

int main(){

    int a;
    a=0;

    struct S s;


    if(a < 5){
        a = a+1;
    }
    else{
        a = a-1;
    }

    if(s){
        a = a+1;
    }

    return 0;
}