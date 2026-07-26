#include <bits/stdc++.h>
using namespace std; 
int a, b; 
char s[10]={67, 79, 76, 79, 82, 32, 48, 48}; 
char c[20]={102, 117, 99, 107, 32, 121, 111, 117, 32, 83, 66, 32, 32, 32}; 
int main(){ 
    srand(114514+1919810); 
    for (int i=1;i<=11;i++) printf("%s%s%s\n", c, c, c); 
    while (1){
        a = rand() % 16; 
        b = rand() % 16;
        s[6] = (a<10)?(a+48):(a+55);
        s[7] = (b<10)?(b+48):(b+55);
        system(s);
        srand(rand());
    }
}