/*
Program (
    StructDecl Person (VarDecl(int), VarDecl(char[50]))
    FunProto add(VarDecl(int), VarDecl(int)) (int)
    FuncDecl main() (int) (
        VarDecl(int)
        VarDecl(int)
        VarDecl(int[5][10])
        VarDecl(struct Person)
        (x = 10)
        (y = 20)
        (((arr[0])[0]) = x)
        (((arr[1])[0]) = y)
        (((arr[2])[0]) = Func Call add (x, y ))
        ((p.age) = 25)
        Func Call strcpy ((p.name), John Doe )
        If ((x < y)) (
            (x = Func Call add (x, y ))
        )
        Else (
            (y = Func Call add (x, y ))
        )

        VarDecl(int)
        (i = 0)
        While ((i < 5)) (
            If ((((arr[i])[2]) == 20)) (
                Break
            )

            If ((((arr[i])[3]) == 10)) (
                (i = (i + 1))
                Continue
            )

            (i = (i + 1))
        )
        return( 0 )
    )
    FuncDecl add(VarDecl(int), VarDecl(int)) (int) (
        return( (a + b) )
    )
)
*/

// Define a structure
struct Person {
    int age;
    char name[50];
};

// Function prototype
int add(int a, int b);

// Main function
int main() {
    int x;
    int y;
    int arr[5][10];
    struct Person p;
    x = 10;
    y = 20;
    arr[0][0] = x;
    arr[1][0] = y;
    arr[2][0] = add(x, y);
    p.age = 25;
    strcpy(p.name, "John Doe");

    if (x < y) {
        x = add(x, y);
    } else {
        y = add(x, y);
    }

    int i;
    i = 0;
    while (i < 5) {
        if (arr[i][2] == 20) {
            break;
        }
        if (arr[i][3] == 10) {
            i = i + 1;
            continue;
        }
        i = i + 1;
    }

    return 0;
}

// Function definition
int add(int a, int b) {
    return a + b;
}