/*
Program (
    FuncDecl f(VarDecl(Integer )) (Integer ) (
        return( 1 )
    )
    FuncDecl main() (Integer ) (
        VarDecl(Integer )
        VarDecl(Integer )
        VarDecl(Integer )
        VarDecl(Integer [1][2])
        (a = (Func Call f (((arr[2])[0]) ) - 5))
        (b = (((*(&(b)) * c) + (2 % 5)) + 2))
        (c = (((10 - 5) > 3) && (1 || (0 == 20))))
        ((arr[1])[2])
        ((mystruct.field)[1])
        ((2 * 3) + 4)
        (2 + (3 * 4))
        &(*(&(b)))
        &((p[1]))
        ((a + b) + c)
        (a = (b = c))
        (a = ((b.c) = d))
        (Structure chancla)(-((s.member)))
        -((Character )((Integer *)((Character )((l.member)))))
        return( 0 )
    )
)
*/

int f(int a){
    return 1;
}

int main(){
    int a;
    int b;
    int c;

    int arr[1][2];

    a = f(arr[2][0]) - 5;
    b = *(&b) * c + 2 % 5 + 2;
    c = 10 - 5 > 3 && 1 || 0 == 20;

    arr[1][2];
    mystruct.field[1];
    2*3+4;
    2+3*4;
    &*(&b);
    &p[1];
    a+b+c;
    a=b=c;
    a=b.c=d;
    (struct chancla)-s.member;
    -(char)(int*)(char)l.member;

    return 0;
}