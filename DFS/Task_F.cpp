#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> depth;
vector<bool> vis;

int dfs(int u) {
    vis[u] = true;
    for (auto v : g[u])  {
        if (vis[v]) {
            continue;
        }

        depth[u] += dfs(v);
    }
    return depth[u];
}

int main() {
    int n;
    cin >> n;
    g.resize(n);
    depth.resize(n, 1);
    vis.resize(n, false);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;

        g[v].push_back(u);
        g[u].push_back(v);
    }

    dfs(0);

    for (auto d : depth) {
        cout << d << ' ';
    }
}