#include <bits/stdc++.h>
#include <numeric>

using namespace std;

vector<vector<int>> g;
vector<int> tin, tup;
vector<bool> vis, ans;
int timer = 0;

void dfs(int u, int p = -1) {
    vis[u] = true;
    tin[u] = tup[u] = timer++;
    int ch = 0;
    for (auto v : g[u]) {
        if (v == p) continue;
        if (vis[v]) { 
            tup[u] = min(tup[u], tin[v]);
        } else {
            dfs(v, u);
            tup[u] = min(tup[u], tup[v]);
            if (tup[v] >= tin[u] && p != -1) {
                ans[u] = true;
            }
            ++ch;
        }
    }

    if (p == -1 && ch > 1) {
        ans[u] = true;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    tin.resize(n);tup.resize(n);
    vis.resize(n);ans.resize(n);

    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v;--u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            dfs(i);
        }
    }


    cout << std::reduce(ans.cbegin(), ans.cend(), 0) << '\n';

    for (int i = 0; i < n; ++i) {
        if (ans[i]) {
            cout << i + 1 << '\n';
        }
    }
}