/*
Program (
    StructDecl s (VarDecl(Integer ), VarDecl(Character ))
    FuncDecl main() (Integer ) (
        VarDecl(Structure s)
        ((x.a) = 5)
        return( 0 )
    )
)
*/

struct s{
    int a;
    char c;
};

int main(){

    struct s x;
    x.a = 5;

    return 0;
}