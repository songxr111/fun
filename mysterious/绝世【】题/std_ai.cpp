#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<long long> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    
    // 计算前缀和
    vector<long long> S(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        S[i] = S[i - 1] + A[i - 1];
    }
    
    // 使用单调栈找到每个位置右边第一个比它小的位置
    vector<int> next_smaller(n + 1, n + 1);
    stack<int> st;
    for (int i = 0; i <= n; i++) {
        while (!st.empty() && S[st.top()] > S[i]) {
            next_smaller[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    
    // 按前缀和值分组存储索引
    map<long long, vector<int>> prefix_sum_indices;
    for (int i = 0; i <= n; i++) {
        prefix_sum_indices[S[i]].push_back(i);
    }
    
    // 统计满足条件的子数组
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long current_sum = S[i];
        int right_bound = next_smaller[i] - 1;
        
        if (right_bound < i + 1) continue;
        
        // 在当前前缀和的分组中查找满足条件的终点
        auto& indices = prefix_sum_indices[current_sum];
        auto left_it = lower_bound(indices.begin(), indices.end(), i + 1);
        auto right_it = upper_bound(indices.begin(), indices.end(), right_bound);
        
        int count = distance(left_it, right_it);
        ans += count;
    }
    
    cout << ans << endl;
    
    return 0;
}