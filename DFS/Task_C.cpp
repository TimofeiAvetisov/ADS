#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> clr;

bool dfs(int v, int c) {
    clr[v] = c;
    for (auto u : g[v]) {
        if (clr[u] == 0) {
            if (!dfs(u, 3 - c)) {
                return false;
            }
        } else if (clr[u] == c) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    g.resize(n);
    clr.resize(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool flag = true;
    for (int i = 0; i < n; ++i) {
        if (clr[i] == 0) {
            if (!dfs(i, 1)) {
                flag = false;
                break;
            }
        }
    }

    cout << (flag ? "YES" : "NO");
}