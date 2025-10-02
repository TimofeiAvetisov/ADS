#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<bool> vis;
int cnt = 0;

void dfs(int v) {
    if (vis[v]) {
        return;
    }
    vis[v] = true;
    ++cnt;
    for (auto u : g[v]) {
        dfs(u);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int x;
    cin >> x;

    g.resize(n);
    vis.resize(n, false);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;--v;
        if (w >= x) {
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }

    dfs(0);

    cout << (vis[n - 1] ? "YES" : "NO");
}