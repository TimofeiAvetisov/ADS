#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> parent;
vector<bool> visited;
int cycle_start = -1, cycle_end = -1;

bool dfs(int v, int par) {
    visited[v] = true;
    for (int u : g[v]) {
        if (u == par) continue;
        if (visited[u]) {
            cycle_start = u;
            cycle_end = v;
            return true;
        }
        parent[u] = v;
        if (dfs(u, v)) return true;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    g.resize(n);
    visited.resize(n, false);
    parent.resize(n, -1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int tmp;
            cin >> tmp;
            if (tmp == 1) {
                g[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (dfs(i, -1)) break;
        }
    }

    if (cycle_start == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.push_back(v);
        }
        reverse(cycle.begin(), cycle.end());

        cout << cycle.size() << "\n";
        for (int v : cycle) {
            cout << v + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}