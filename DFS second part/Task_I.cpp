#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> pr, d;
vector<bool> vis;

void dfs(int u, int p = -1) {
    if (vis[u]) return;

    vis[u] = true;
    pr[u] = p;
    for (auto v : g[u]) {
        if (v != p) {
            dfs(v, u);
            d[u] += d[v];
        }
    }
}

int main() {
    int n;
    cin >> n;
    g.resize(n);
    vis.resize(n);pr.resize(n);d.resize(n, 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;

        g[v].push_back(u);
        g[u].push_back(v);
    }

    int answer = -2;

    dfs(0);

    for (int i = 0; i < n && answer == -2; ++i) {
        int tmp = 0;
        int sz = g[i].size();
        if (sz <= 1 || (sz > 0 && (n - 1) % sz != 0)) {
            continue;
        }

        int cmp_sz = (n - 1) / (sz);
        bool flag = true;
        for (auto v : g[i]) {
            if (v != pr[i]) {
                if (d[v] != cmp_sz) {
                    flag = false;
                    break;
                }
            }
        }

        if (flag) {
            answer = i;
        }
    }

    cout << answer + 1;
}