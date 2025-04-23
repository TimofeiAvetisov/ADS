#include <bits/stdc++.h>

using namespace std;
#define int long long

signed main() {
    int n, m, k, c;
    cin >> n >> m >> k >> c;
    --c;
    vector<int> cities(k);
    for (int i = 0; i < k; ++i) {
        cin >> cities[i];
        --cities[i];
    }

    vector<vector<pair<int, int>>> g(n);
    vector<int> d(n, LONG_LONG_MAX);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;--v;
        g[v].push_back({u, w});
        g[u].push_back({v, w});
    }
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, c});
    d[c] = 0;

    while(!q.empty()) {
        auto [dist, v] = q.top(); q.pop();
        if (dist > d[v]) continue;

        for (auto [u, w] : g[v]) {
            if (d[u] > d[v] + w) {
                d[u] = d[v] + w;
                q.push({d[u], u});
            }
        }
    }

    set<pair<int, int>> ans;
    for (auto city : cities) {
        ans.insert({ d[city], city});
    }

    for (auto [dist, city] : ans) {
        cout << city + 1 << ' ' << dist << '\n';
    }
}