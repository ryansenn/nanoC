/*
Program (
    FuncDecl main() (Integer, p count: 0, array size: ) (
        VarDecl(Integer, p count: 0, array size: )
        (i = 1)
        If (i) (
            (1 + 1)
            (2 + 2)
        )
        Else (
            (3 + 3)
        )

        If ((i == 3)) (
            (2 + 2)
        )

        If ((1 > 2)) (
(i = 2)        )
        Else (
(i = 3)        )

        return( 0 )
    )
)
*/

int main(){
    int i;
    i = 1;

    if (i){
        1 + 1;
        2 + 2;
    }
    else{
        3+3;
    }

    if (i == 3){
        2+2;
    }

    if (1 > 2)
        i=2;
    else
        i=3;

    return 0;
}