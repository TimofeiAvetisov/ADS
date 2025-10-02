#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> deg(n);
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;
        ++deg[u];++deg[v];
        edges[i] = {u, v};
    }

    vector<vector<int>> g(n);
    for (auto [u, v] : edges) {
        if (deg[u] < deg[v] || (deg[u] == deg[v] && u < v)) {
            g[v].push_back(u);
        } else {
            g[u].push_back(v);
        }
    }


    int ans = 0;
    vector<int> used(n);
    for (int u = 0; u < n; ++u) {
        for (auto v : g[u]) {
            used[v] = u + 1;
        }

        for (auto v : g[u]) {
            for (auto w : g[v]) {
                if (used[w] == u + 1) {
                    ++ans;
                }
            }
        }
    }

    cout << ans;
}