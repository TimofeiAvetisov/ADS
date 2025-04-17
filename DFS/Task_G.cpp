#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> dist;

void dfs(int u, int d, int start = 0) {
    dist[u] = d;
    for (auto v : g[u]) {
        if (v == start || dist[v] != 0) {
            continue;
        }
        dfs(v, d + 1, start);
    }
}

int main() {
    int n;
    cin >> n;
    g.resize(n);
    dist.resize(n, 0);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(0, 0);

    int max_v, max_dist;
    max_v = -1;max_dist = 0;
    for (int i = 0; i < n; ++i) {
        if (max_dist < dist[i]) {
            max_v = i;
            max_dist = dist[i];
        }
    }

    dist.assign(n, 0);
    dfs(max_v, 0, max_v);

    cout << *max_element(dist.begin(), dist.end());
}