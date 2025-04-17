#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    vector<int> d(n, LONG_LONG_MAX), vis(n, false), pr(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;--v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    int s, f;
    cin >> s >> f;
    --s;--f;

    d[s] = 0;
    pr[s] = -1;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [dist, v] = q.top(); q.pop();
        if (dist > d[v]) continue;

        for (auto [u, w] : g[v]) {
            if (d[u] > d[v] + w) {
                d[u] = d[v] + w;
                q.push({d[u], u});
                pr[u] = v;
            }
        }
    }

    if (d[f] == LONG_LONG_MAX) {
        cout << -1;
        return 0;
    }
    cout << d[f] << '\n';
    vector<int> path;
    while (pr[f] != -1) {
        path.push_back(f);
        f = pr[f];
    }
    path.push_back(s);
    reverse(path.begin(), path.end());
    cout << path.size() << '\n';
    for (auto p : path) {
        cout << p + 1 << ' ';
    }
}