#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> vis;
vector<int> answer;
bool flag = false;

void dfs(int u) {

    vis[u] = 1;
    for (auto v : g[u]) {
        if (vis[v] == 1) {
            flag = true;
        }
        if (vis[v] == 0) {
            dfs(v);
        }
    }
    vis[u] = 2; 
    answer.push_back(u);
}

int main() {
    int n,m;
    cin >> n >> m;
    g.resize(n);
    vis.resize(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;
        g[u].push_back(v);
    }
    for (int i = 0; i < n; ++i) {
        if (vis[i] == 0) {
            dfs(i);
        }
    }
    if (flag) {
        cout << -1;
        return 0;
    }
    for (int i = answer.size() - 1; i >= 0; --i) {
        cout << answer[i] + 1 << ' ';   
    }
}