#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, rev, c;
};

const int INF = 1e9;
int p;
vector<vector<Edge>> g;
vector<int> lvl, ptr;

int dfs(int v, int flow, int n) {
    if (v == n - 1 || flow == 0) {
        return flow;
    }

    for (int &i = ptr[v]; i < g[v].size(); ++i) {
        auto &edge = g[v][i];
        if (edge.c > 0 && lvl[edge.v] == lvl[v] + 1) {
            if ((p = dfs(edge.v, min(flow, edge.c), n)) != 0) {
                edge.c -= p;
                g[edge.v][edge.rev].c += p;
                return p;
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    g.resize(n, {}); lvl.resize(n, -1); ptr.resize(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        --u; --v;
        g[u].emplace_back(v, (int)g[v].size(), c);
        g[v].emplace_back(u, (int)g[u].size(), 0);
    }

    int ans = 0;
    while (true) {
        fill(lvl.begin(), lvl.end(), -1);
        queue<int> q;
        lvl[0] = 0;
        q.push(0);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &edge : g[v]) {
                if (edge.c > 0 && lvl[edge.v] == -1) {
                    lvl[edge.v] = lvl[v] + 1;
                    q.push(edge.v);
                }
            }
        }

        if (lvl[n - 1] == -1) {
            break;
        }

        fill(ptr.begin(), ptr.end(), 0);
        while (int flow = dfs(0, INF, n))
            ans += flow;
    }
    cout << ans;
}
