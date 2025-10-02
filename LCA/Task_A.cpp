#include <bits/stdc++.h>

using namespace std;

vector<int> tin, tout;
vector<bool> vis;
vector<vector<int>> g;
int timer = 0;

void dfs(int v) {
    if (vis[v]) {
        return;
    }

    vis[v] = true;
    tin[v] = timer;
    ++timer;
    for (auto u : g[v]) {
        dfs(u);
    }
    tout[v] = timer;
    ++timer;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    tin.resize(n, 0);tout.resize(n, 0);vis.resize(n, false);
    g.resize(n);
    int root = -1;
    for (int i = 0; i < n; ++i) {
        int  v;
        cin >> v;
        if (v == 0) {
            root = i;
            continue;
        }
        g[v - 1].push_back(i);
    }

    dfs(root);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;
        cout << (tin[v] > tin[u] && tin[v] < tout[u]) << '\n';
    }
}