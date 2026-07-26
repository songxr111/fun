#include <bits/stdc++.h>
#define p(a) s[now++]=a,
using namespace std;
char s[1000000]={115, 116, 97, 114, 116, 32, 99, 109, 100, 32, 47, 107, 32, 34, 99, 111, 108, 111, 114, 32, 48, 48, 32, 38, 32};
int main(){
    int t=1000;
    int now=strlen(s); 
    p(116)p(105)p(116)p(108)p(101)p(32)p(78)p(79)p(32)p(74)p(67)p(33)p(32)0;
    for (int i=1;i<=20;i++){
        p(38)p(32)p(101)p(99)p(104)p(111)p(32)0;
        for(int j=1;j<=15;j++) p(78)p(79)p(32)p(74)p(67)p(33)p(32)p(32)0;
    }
    p(34)0;
    srand(time(0));
    while (t--){
        srand(rand());
        int a = rand()%16;
        int b = rand()%16;
        a += a>=10?55:48;
        b += b>=10?55:48;
        s[20]=a;s[21]=b;
        system(s);
    }
}
