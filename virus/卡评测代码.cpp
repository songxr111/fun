#include <iostream>
#include <bits/stdc++.h>
typedef long long ll;
const ll N = 1e18+300;
//...

ll f(ll x){
	if (x<=1) return 1ll;
	ll a[N]={1,4,3,24,5,524,5,24,4334,4,55,5,24,33524,56,23,8};
//	a[114514] = 2/0;
	return f(x-1)+f(x-2);
}
int main(){
	while (81){
		ll ans = f(N);
	}
	return -1000;
}
