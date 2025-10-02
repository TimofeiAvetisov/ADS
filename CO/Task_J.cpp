#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    int limit = (1 << n);

    int x = 0;
    vector<pair<pair<int, int>, int>> edges;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w;
            cin >> w;
            if (w != 0 && i > j) {
                edges.push_back({{i, j}, w});
            }
        }
    }
    int ans = 0;
    int max_x = 0;
    while (x < limit) {
        int tmp_ans = 0;
        for (auto [cord, w] : edges) {
            tmp_ans += ( ((x >> cord.first) ^ (x >> cord.second)) & 1 ) * w;
        }
        if (tmp_ans > ans) {
            ans = tmp_ans;
            max_x = x;
        }
        ++x;
    }

    cout << ans << '\n';
    for (int i = 0; i < n; ++i) {
        cout << ((max_x >> i) & 1) + 1 << ' ';
    }
}