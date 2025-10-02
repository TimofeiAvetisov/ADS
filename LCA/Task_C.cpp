#include <bits/stdc++.h>

using namespace std;

vector<int> tin, tout, d;
vector<vector<int>> g, _d;
int max_d = -1, timer = 0;



void dfs(int v, int pr) {
    d[v] = d[pr] + 1;
    max_d = max(max_d, d[v]);
    _d[d[v]].push_back(timer);
    tin[v] = timer;
    ++timer;
    for (auto u : g[v]) {
        dfs(u, v);
    }
    tout[v] = timer;
    ++timer;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, root;
    cin >> n;
    tin.resize(n);tout.resize(n);d.resize(n);_d.resize(n);g.resize(n);
    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        if (v == -1) {
            root = i;
            continue;
        }
        g[v - 1].push_back(i);
    }

    d[root] = -1;
    dfs(root, root);

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int v, k;
        cin >> v >> k;
        --v;
        if (k + d[v] >= n) {
            cout << 0 << '\n';
            continue;
        }
        auto &target = _d[k + d[v]];
        cout << lower_bound(target.begin(), target.end(), tout[v]) - lower_bound(target.begin(), target.end(), tin[v]) << '\n';
    }
}