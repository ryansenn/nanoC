/*
Semantic error: Invalid type cast from 'int*' to 'int' at line 12 column 9
*/

int main(){
    int* a;
    char b;

    (int) b;
    (char*) a;

    (int) a;

    return 0;
}