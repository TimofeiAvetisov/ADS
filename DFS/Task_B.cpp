#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> vis;
unordered_map<int, vector<int>> cmp;

void dfs(int v, int clr) {
    if (vis[v] != 0) return;

    vis[v] = clr;
    cmp[clr].push_back(v);

    for (auto u : g[v]) {
        dfs(u, clr);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vis.resize(n, 0);
    g.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --v;--u;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int clr = 1;
    for (int i = 0; i < n; ++i) {
        if (vis[i] == 0) {
            dfs(i, clr);
            ++clr;
        }
    }

    cout << clr - 1 << '\n';
    for (int i = 1; i < clr; ++i) {
        cout << cmp[i].size() << '\n';
        for (auto v : cmp[i]) {
            cout << v + 1 << ' ';
        }
        cout << '\n';
    }
}