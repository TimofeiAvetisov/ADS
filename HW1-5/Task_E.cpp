#include <bits/stdc++.h>

using namespace std;

#define int long long

int n, m;

int dj(int s, vector<vector<pair<int, int>>>& g, vector<int> c) {
    vector<int> d(n, INT64_MAX), vis(n, false);

    d[s] = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int i = 0; i < n; ++i) {
            if (!(vis[i]) && (v == -1 || d[v] > d[i])) {
                v = i;
            }
        }

        vis[v] = true;
        for (auto [u, w] : g[v]) {
            d[u] = min(d[u], d[v] + w);
        }
    }

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        ans += d[i] * c[i];
    }

    return ans;
}

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        cin >> cnt[i];
    }

    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v ,w;
        cin >> u >> v >> w;
        --u;--v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    int ans = -1;
    for (int i = 0; i < n; ++i) {
        int tmp_ans = dj(i, g, cnt);
        if (ans == -1 || tmp_ans < ans) {
            ans = tmp_ans;
        }
    }

    cout << ans;
}