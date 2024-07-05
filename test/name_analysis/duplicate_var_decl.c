/*
Semantic error: Identifier 'a' has already been declared in the same scope at line 12 column 17
*/
int main(){

    int a;

    {
        char a;
        {
            int a;
            char a;
        }
    }

    return 0;
}