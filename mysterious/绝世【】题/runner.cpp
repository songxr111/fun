#include <bits/stdc++.h>
using namespace std;
int main(){
    for (int i=1;i<=100000;++i){
        system("maker.exe");
        system("std_ai.exe");
        system("std_mine.exe");
        if (system("fc balance.out balance.ans")){
            fprintf(stderr, "Test %d: WA!!!!\n", i);
            return 1;
        }
        fprintf(stderr, "Test %d: AC\n", i);
    }
    return 0;
}
