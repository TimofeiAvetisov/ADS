#include <bits/stdc++.h>

using namespace std;

const int mod = 16714589;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, a_1;
    cin >> n >> q >> a_1;
    vector<int> a(n);
    a[0] = a_1;
    for (int i = 1; i < n; i++) {
        a[i] = (23 * a[i - 1] + 21563) % mod; 
    }

    int k = __lg(n) + 1;
    vector<vector<int>> sparse_table(k, vector<int>(n));
    sparse_table[0] = a;

    vector<int> lg(n + 1);
    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }

    for (int j = 1; j < k; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            sparse_table[j][i] = min(sparse_table[j - 1][i], sparse_table[j - 1][i + (1 << (j - 1))]);
        }
    }

    auto rmq = [&](int l, int r) {
        int d = r - l + 1;
        int j = lg[d];
        return min(sparse_table[j][l], sparse_table[j][r - (1 << j) + 1]);
    };

    int u, v;
    cin >> u >> v;
    long long answer = 0;
    for (int i = 0; i < q - 1; ++i) {
        int ans = rmq(min(u - 1, v - 1), max(u - 1, v - 1));
        u = ((17 * u + 751 + ans + 2 * (i + 1)) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * (i + 1)) % n) + 1;

    }

    cout << u << ' ' << v << ' ' << rmq(min(u - 1, v - 1), max(u -  1, v - 1));
}
