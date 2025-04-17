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
    int n, m;
    cin >> n >> m;
    vis.resize(n, false);
    g.resize(n);

    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        g[v - 1].push_back(u - 1);
        g[u - 1].push_back(v - 1);
    }

    dfs(0);

    cout << cnt << '\n';
    for (int i = 0; i < n; ++i) {
        if (vis[i]) {
            cout << i + 1 << ' ';
        }
    }
}