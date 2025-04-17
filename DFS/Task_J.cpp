#include <bits/stdc++.h>

using namespace std;
vector<vector<int>> g;
vector<vector<bool>> vis;
vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool dfs(int i, int j) {
    vis[i][j] = true;
    bool flag = false;
    for (auto p : moves) {
        int new_i = p.first + i;
        int new_j = p.second + j;
        if (new_i >= 0 && new_i < g.size() && new_j >= 0 && new_j < g[i].size()) {
            if (g[i][j] > g[new_i][new_j]) {
                flag = true;
                continue;
            }
            if (!vis[new_i][new_j] && g[new_i][new_j] == g[i][j]) {
                flag = flag || dfs(new_i, new_j);
            }
        }
    }
    return flag;
}

int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n, vector<int>(m, 0));
    vis.resize(n, vector<bool>(m, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> g[i][j];
        }
    }

    int ans = 0;
    vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!vis[i][j] && !dfs(i, j)) {
                ++ans;
            }
        }
    }

    cout << ans << '\n';    
}