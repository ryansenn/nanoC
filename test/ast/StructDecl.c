/*
Program (
    StructDecl s (VarDecl(Integer, p count: 0, array size: ), VarDecl(Character, p count: 0, array size: ))
    FuncDecl main() (Integer, p count: 0, array size: ) (
        VarDecl(Structure, p count: 0, array size: )
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