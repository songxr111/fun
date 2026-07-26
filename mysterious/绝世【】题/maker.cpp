#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// 生成随机整数在[min_value, max_value]范围内
long long rand_long(long long min_value, long long max_value) {
    static mt19937_64 gen(time(nullptr));
    uniform_int_distribution<long long> dist(min_value, max_value);
    return dist(gen);
}

// 生成随机序列
vector<long long> generate_random_sequence(int n, long long min_val, long long max_val) {
    vector<long long> A(n);
    for (int i = 0; i < n; i++) {
        A[i] = rand_long(min_val, max_val);
    }
    return A;
}

// 生成全正序列
vector<long long> generate_positive_sequence(int n, long long min_val, long long max_val) {
    vector<long long> A(n);
    for (int i = 0; i < n; i++) {
        A[i] = rand_long(min_val, max_val);
    }
    return A;
}

// 生成全负序列
vector<long long> generate_negative_sequence(int n, long long min_val, long long max_val) {
    vector<long long> A(n);
    for (int i = 0; i < n; i++) {
        A[i] = rand_long(min_val, max_val);
    }
    return A;
}

// 生成交替序列，如1, -1, 1, -1, ...
vector<long long> generate_alternating_sequence(int n, long long positive, long long negative) {
    vector<long long> A(n);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            A[i] = positive;
        } else {
            A[i] = negative;
        }
    }
    return A;
}

// 生成由正负对组成的序列（可能包含平衡子数组）
vector<long long> generate_balanced_pairs_sequence(int n) {
    vector<long long> A;
    if (n % 2 != 0) {
        n--;
    }
    for (int i = 0; i < n/2; i++) {
        long long positive = rand_long(1, 1000000000);
        A.push_back(positive);
        A.push_back(-positive);
    }
    if (A.size() < n) {
        A.push_back(0);
    }
    return A;
}

// 生成真正的平衡序列：前缀和始终非负且总和为0
vector<long long> generate_true_balanced_sequence(int n) {
    vector<long long> A;
    if (n < 2) {
        A.push_back(0);
        return A;
    }
    int k = rand_long(1, n-1);
    int m = n - k;
    long long total_positive = 0;
    for (int i = 0; i < k; i++) {
        long long positive = rand_long(1, 1000000000);
        A.push_back(positive);
        total_positive += positive;
    }
    long long remaining = total_positive;
    for (int i = 0; i < m; i++) {
        if (i == m-1) {
            A.push_back(-remaining);
            remaining = 0;
        } else {
            long long negative_abs = rand_long(1, remaining);
            A.push_back(-negative_abs);
            remaining -= negative_abs;
        }
    }
    return A;
}

// 生成一个特殊序列，其前缀和具有多个最小值点
vector<long long> generate_multiple_minima_sequence(int n) {
    vector<long long> A;
    int segments = rand_long(2, min(n/2, 10)); // 2到10个段
    vector<int> segment_sizes(segments, 0);
    int remaining = n;
    for (int i = 0; i < segments-1; i++) {
        segment_sizes[i] = rand_long(1, remaining - (segments - i - 1));
        remaining -= segment_sizes[i];
    }
    segment_sizes[segments-1] = remaining;
    
    long long base = 0;
    for (int i = 0; i < segments; i++) {
        int seg_size = segment_sizes[i];
        // 每个段内生成一个小范围的变化
        for (int j = 0; j < seg_size; j++) {
            long long val;
            if (i % 2 == 0) {
                val = rand_long(1, 100);
            } else {
                val = rand_long(-100, -1);
            }
            A.push_back(val);
        }
        // 在段之间添加一个大值，确保前缀和的最小值出现在段边界
        if (i < segments-1) {
            if (i % 2 == 0) {
                A.push_back(rand_long(1000, 10000));
            } else {
                A.push_back(rand_long(-10000, -1000));
            }
        }
    }
    return A;
}

int main(int argc, char* argv[]) {
    freopen("balance.in", "w", stdout);
    int n = 1000000;
    string type = "random";
    long long min_val = -1000000000;
    long long max_val = 1000000000;
    
    // 解析命令行参数
    if (argc > 1) {
        n = stoi(argv[1]);
    }
    if (argc > 2) {
        type = argv[2];
    }
    if (argc > 3) {
        min_val = stoll(argv[3]);
    }
    if (argc > 4) {
        max_val = stoll(argv[4]);
    }
    
    vector<long long> A;
    
    if (type == "random") {
        A = generate_random_sequence(n, min_val, max_val);
    } else if (type == "positive") {
        A = generate_positive_sequence(n, max(1LL, min_val), max_val);
    } else if (type == "negative") {
        A = generate_negative_sequence(n, min_val, min(-1LL, max_val));
    } else if (type == "alternating") {
        long long pos = (argc > 3) ? stoll(argv[3]) : 1;
        long long neg = (argc > 4) ? stoll(argv[4]) : -1;
        A = generate_alternating_sequence(n, pos, neg);
    } else if (type == "balanced_pairs") {
        A = generate_balanced_pairs_sequence(n);
    } else if (type == "true_balanced") {
        A = generate_true_balanced_sequence(n);
    } else if (type == "multiple_minima") {
        A = generate_multiple_minima_sequence(n);
    } else {
        cerr << "Unknown type. Available types: random, positive, negative, alternating, balanced_pairs, true_balanced, multiple_minima" << endl;
        return 1;
    }
    
    // 输出到标准输出
    cout << n << endl;
    for (size_t i = 0; i < A.size(); i++) {
        if (i > 0) cout << " ";
        cout << A[i];
    }
    cout << endl;
    
    return 0;
}
