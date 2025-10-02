#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;

    --a;--b;
    int d;
    cin >> d;

    vector<vector<pair<int, int>>> g(n);
    vector<pair<int, int>> dist(n, {INT_MAX, INT_MAX});
    vector<int> vis(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;--v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    dist[a] = {0, 0};

    for (int i = 0; i < n && !vis[b]; ++i) {
        int v = -1;
        for (int i = 0; i < n; ++i) {
            if (!(vis[i]) && (v == -1 || dist[v] > dist[i])) {
                v = i;
            }
        }

        vis[v] = true;
        for (auto [u, w] : g[v]) {
            pair<int, int> time = dist[v];
            if (time.second + w > d) {
                time = {time.first + 1, w};
            } else {
                time = {time.first, time.second + w};
            }
            dist[u] = min(dist[u], time);
        }
    }

    if (dist[b].first == INT_MAX && dist[b].second == INT_MAX) {
        cout << -1;
        return 0;
    }
    cout << dist[b].first + 1 << '\n';
}