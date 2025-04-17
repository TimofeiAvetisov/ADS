#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g, g_t;
vector<bool> vis;
vector<int> ts, cmp;
int cmp_clr = 0;

void top_sort(int v) {
    if (vis[v]) return;
    vis[v] = true;
    for (int u : g[v]) {
        top_sort(u);
    }
    ts.push_back(v);
}

void dfs(int v) {
    if (cmp[v] != 0) {
        return;
    }

    cmp[v] = cmp_clr;
    for (auto u : g_t[v]) {
        dfs(u);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n); g_t.resize(n);
    vis.resize(n); cmp.resize(n);

    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v;--u;
        g[v].push_back(u);
        g_t[u].push_back(v);
    }

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            top_sort(i);
        }
    }

    reverse(ts.begin(), ts.end());
    for (int v : ts) {
        if (cmp[v] == 0) {
            ++cmp_clr;
            dfs(v);
        }
    }

    cout << cmp_clr << '\n';

    for (auto q : cmp) {
        cout << q << ' ';
    }
}