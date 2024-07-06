/*
Program (
    FuncDecl f(VarDecl(int), VarDecl(char[])) (void) (
        return(  )
    )
    FuncDecl h(VarDecl(struct s*)) (int) (
        return( 1 )
    )
    FunProto k() (char*)
    FuncDecl main() (int) (
        return( 0 )
    )
)
*/

void f(int a, char arr[]){
    return;
}

int h(struct s* p){
    return 1;
}

char* k();

int main(){
    return 0;
}