/*
Program (
    StructDecl s (VarDecl(int), VarDecl(char))
    FuncDecl main() (int) (
        VarDecl(struct s)
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