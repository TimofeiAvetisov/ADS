#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<bool> vis;

void dfs(int u) {
    vis[u] = true;
    for (auto v : g[u]) {
        if (!vis[v]) dfs(v);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vis.resize(n, false);
    g.resize(n);
    vis[0] = true;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        if (u == v) {
            continue;
        }
        g[v].push_back(u);
    }

    dfs(0);

    for (int i = 0; i < n; ++i) {
        if (vis[i]) {
            cout << i + 1 << ' ';
        }
    }
}