#include <bits/stdc++.h>

using namespace std;

void dfs(int v, vector<vector<int>>& g, vector<bool>& vis) {
    if (vis[v] == true) {
        return;
    }

    vis[v] = true;
    for (auto u : g[v]) {
        dfs(u, g, vis);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> gw(n), gs(n);
    vector<vector<bool>> viss(n, vector<bool>(n, false)), visw(n, vector<bool>(n, false));

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            char tmp;
            cin >> tmp;

            if (tmp == 'S') {
                gs[i].push_back(j);
            } else {
                gw[i].push_back(j);

            }
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        for (auto v : gs[i]) {
            viss[i][v] = true;
            for (int u = 0; u < n; ++u) {
                viss[i][u] = viss[i][u] || viss[v][u];
            }
        }
        for (auto v : gw[i]) {
            visw[i][v] = true;
            for (int u = 0; u < n; ++u) {
                visw[i][u] = visw[i][u] || visw[v][u];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (viss[i][j] && visw[i][j]) {
                cout << "NO";
                return 0;
            }
        }
    }
    cout << "YES" << '\n';
}