/*
Semantic error: Identifier 'a' has already been declared in the same scope at line 9 column 9
*/

struct s{
    int a;
    char b;
    int c;
    char a;
};

int main(){
    return 0;
}