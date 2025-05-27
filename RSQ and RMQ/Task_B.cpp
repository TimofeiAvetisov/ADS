#include <bits/stdc++.h>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
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

    int q;
    cin >> q;
    long long answer = 0;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        answer += rmq(l, r);
    }

    cout << answer;
}
