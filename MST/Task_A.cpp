#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;--v;
        g[v].emplace_back(u, w);
        g[u].emplace_back(v, w);
    }

    set<pair<int, int>> q;
    vector<int> d(n, INT_MAX);
    d[0] = 0;
    q.insert({0, 0});
    vector<bool> vis(n, false);

    int answer = 0;

    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());

        if (vis[v]) continue;

        vis[v] =true;
        answer += d[v];

        for (auto [u, w] : g[v]) {
            if (w < d[u]) {
                q.erase({d[u], u});
                d[u] = w;
                q.insert({d[u], u});
            }
        }
    }

    cout << answer;
}