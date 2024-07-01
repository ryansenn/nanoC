/*
Program (
    StructDecl Person (VarDecl(Integer, p count: 0, array size: ), VarDecl(Character, p count: 0, array size: 50 ))
    FunProto add(VarDecl(Integer, p count: 0, array size: ), VarDecl(Integer, p count: 0, array size: )) (Integer, p count: 0, array size: )
    FuncDecl main() (Integer, p count: 0, array size: ) (
        VarDecl(Integer, p count: 0, array size: )
        VarDecl(Integer, p count: 0, array size: )
        VarDecl(Integer, p count: 0, array size: 5 10 )
        VarDecl(Structure, p count: 0, array size: )
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

        VarDecl(Integer, p count: 0, array size: )
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
    FuncDecl add(VarDecl(Integer, p count: 0, array size: ), VarDecl(Integer, p count: 0, array size: )) (Integer, p count: 0, array size: ) (
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