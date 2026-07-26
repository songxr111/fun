#include <cstdio>
#include <vector>
#include <algorithm>
const int SZ = 1<<23;
char ch, buf[SZ], *p1, *p2;
#define ge() (p1==p2&&(p2=buf+fread(p1=buf, 1, SZ, stdin), p1==p2)?EOF:*p1++)
typedef long long ll;
template <typename T>
inline void read(T &x) {
    x=0;bool sgn=0;
    while ('0'>ch||ch>'9') ch=ge(), sgn |= (ch=='-');
    while ('0'<=ch&&ch<='9') x=x*10+ch-'0', ch=ge();
    if (sgn) x=-x;
}
const int N = 1e6+5;
int n, sta[N], top, rig[N], cnt;
ll a[N], nums[N], ans;
std::vector<int> b[N];
int main() {
    freopen("balance.in", "r", stdin);
    freopen("balance.ans", "w", stdout);
    read(n);
    for (int i=1;i<=n;++i) read(a[i]), a[i] += a[i-1], nums[i] = a[i];
    std::sort(nums, nums+1+n);
    cnt = std::unique(nums, nums+1+n)-nums-1;
    for (int i=0;i<=n;++i){
        a[i] = std::lower_bound(nums, nums+1+cnt, a[i])-nums;
        b[a[i]].emplace_back(i);
        while (top&&a[sta[top]]>a[i]) rig[sta[top]] = i, --top;
        sta[++top] = i;
    }
    for (int i=0;i<=n;++i){
        if (!rig[i]) rig[i] = n+1;
        ans += std::upper_bound(b[a[i]].begin(), b[a[i]].end(), rig[i])-upper_bound(b[a[i]].begin(), b[a[i]].end(), i);
    }
    printf("%lld", ans);
    return 0;
}