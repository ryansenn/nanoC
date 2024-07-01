/*
Program (
    FuncDecl main() (Integer, p count: 0, array size: ) (
        VarDecl(Integer, p count: 0, array size: )
        (i = 0)
        While ((i < 10)) (
            (i = (i + 1))
            Break
        )
        While (i) (
            Continue
        )
        (i = 0)
        While ((i < 5)) (
(i = (i * 2))        )
        return( 0 )
    )
)
*/

int main(){
    int i;
    i = 0;

    while (i < 10){
        i = i + 1;
        break;
    }

    while (i) {
        continue;
    }

    i = 0;

    while (i < 5)
        i = i * 2;

    return 0;
}