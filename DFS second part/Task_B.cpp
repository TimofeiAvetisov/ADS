#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> tin, tup;
vector<bool> vis;
set<int> answer;
int timer = 0;
map<pair<int, int>, int> edges, cnt;

inline pair<int, int> form_edge(int v, int u) {
    return {min(u, v), max(u, v)};
}

void dfs(int v, int p = -1) {
    vis[v] = true;
    tup[v] = tin[v] = timer++;
    for (auto u : g[v]) {
        if (u == p) continue;

        if (vis[u]) {
            tup[v] = min(tup[v], tin[u]);
        } else {
            dfs(u, v);
            tup[v] = min(tup[v], tup[u]);
            if (tup[u] > tin[v] && cnt[form_edge(u, v)] == 1) {
                answer.insert
                (edges[form_edge(u, v)]);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    vis.resize(n, false);
    tin.resize(n); tup.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> v >> u;
        --v;--u;
        edges[form_edge(v, u)] = i + 1;
        cnt[form_edge(v, u)] += 1;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            dfs(i);
        }
    }

    cout << answer.size() << '\n';
    for(auto q : answer) {
        cout << q << '\n';
    }
}