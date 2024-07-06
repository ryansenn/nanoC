/*
Semantic error: Struct 's' has already been declared
*/

struct s{
    int a;
    char b;
    int c;
};

struct s1{
    int a;
    char b;
    int c;
};

struct s{};

int main(){
    return 0;
}