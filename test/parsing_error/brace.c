/*
Parsing error: Expected primary expression (int lit, char lit, string lit, identifier or func call) at line 7 column 13 found Else
*/
int main(){
    if (1) {
        1 + 1;
        else{
            2 + 2;
        }

        return 0;
    }