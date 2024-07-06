/*
Include stdio.h
struct
Identifier test_struct
Left Brace
int
Identifier a
Semicolon
char
Identifier b
Semicolon
Right Brace
Semicolon
int
Identifier main
Left Parenthesis
Right Parenthesis
Left Brace
int
Identifier x
Semicolon
Identifier x
=
Integer Literal 10
Semicolon
int
Identifier y
Semicolon
Identifier y
=
Integer Literal 20
Semicolon
char
Identifier c
Semicolon
Identifier c
=
Character Literal A
Semicolon
char
*
Identifier str
Semicolon
Identifier str
=
String Literal Hello, World!
Semicolon
void
*
Identifier ptr
Semicolon
struct
Identifier test_struct
Identifier s
Semicolon
If
Left Parenthesis
Identifier x
==
Identifier y
||
Identifier x
!=
Identifier y
&&
Identifier x
<
Identifier y
||
Identifier x
>
Identifier y
||
Identifier x
<=
Identifier y
||
Identifier x
>=
Identifier y
Right Parenthesis
Left Brace
Identifier x
=
Identifier x
+
Identifier y
-
Integer Literal 5
*
Integer Literal 3
/
Integer Literal 2
%
Integer Literal 4
Semicolon
Right Brace
While
Left Parenthesis
Identifier x
>
Integer Literal 0
Right Parenthesis
Left Brace
If
Left Parenthesis
Identifier x
%
Integer Literal 2
==
Integer Literal 0
Right Parenthesis
Left Brace
Continue
Semicolon
Right Brace
Else
Left Brace
Break
Semicolon
Right Brace
Identifier x
=
Identifier x
-
Integer Literal 1
Semicolon
Right Brace
int
Identifier size
Semicolon
Identifier size
=
Sizeof
Left Parenthesis
struct
Identifier test_struct
Right Parenthesis
Semicolon
Identifier s
.
Identifier a
=
Integer Literal 100
Semicolon
Identifier s
.
Identifier b
=
Character Literal B
Semicolon
Return
Integer Literal 0
Semicolon
Right Brace

*/

#include <stdio.h>

struct test_struct {
    int a;
    char b;
};

int main() {
    int x;
    x = 10;
    int y;
    y = 20;
    char c;
    c = 'A';
    char* str;
    str = "Hello, World!";
    void* ptr;
    struct test_struct s;

    // Testing operators
    if (x == y || x != y && x < y || x > y || x <= y || x >= y) {
        x = x + y - 5 * 3 / 2 % 4;
    }

    // Testing keywords and control structures
    while (x > 0) {
        if (x % 2 == 0) {
            continue;
        } else {
            break;
        }
        x=x-1;
    }

    // Testing sizeof and struct
    int size;
    size = sizeof(struct test_struct);
    s.a = 100;
    s.b = 'B';

    // Testing function call and return
    return 0;
}

/* This is a multi-line comment
   to test comment tokenization */

// This is a single-line comment