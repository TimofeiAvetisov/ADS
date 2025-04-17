#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> g;
vector<int> tin, tup, pr;
vector<bool> vis, is_bridge;
map<pair<int, int>, int> cnt;
int timer = 0;

inline pair<int, int> make_edge(int u, int v) {
    return {min(u, v), max(u, v)};
}

void find_bridges(int u, int p = -1) {
    vis[u] = true;
    tin[u] = tup[u] = ++timer;
    pr[u] = p;
    
    for (auto [v, idx] : g[u]) {
        if (v == p) continue;
        
        if (vis[v]) {
            tup[u] = min(tup[u], tin[v]);
        } 
        else {
            find_bridges(v, u);
            tup[u] = min(tup[u], tup[v]);
            if (tup[v] > tin[u] && cnt[make_edge(u, v)] == 1) {
                is_bridge[idx] = true;
            }
        }
    }
}

vector<pair<int, int>> direction;
vector<bool> used;

void orient_dfs(int u) {
    used[u] = true;
    for (auto [v, idx] : g[u]) {
        if (direction[idx] == make_pair(-1, -1)) {
            direction[idx] = {u, v};
            if (!used[v]) {
                orient_dfs(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    g.resize(n);
    direction.assign(m, {-1, -1});
    vector<pair<int, int>> edges(m);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        edges[i] = {u, v};
        cnt[make_edge(u, v)]++;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    tin.resize(n);
    tup.resize(n);
    pr.resize(n);
    vis.assign(n, false);
    is_bridge.assign(m, false);
    
    find_bridges(0);

    bool has_bridges = false;
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edges[i];
        if (is_bridge[i] && cnt[make_edge(u, v)] == 1) {
            has_bridges = true;
            break;
        }
    }

    if (has_bridges) {
        cout << 0 << '\n';
        return 0;
    }

    used.assign(n, false);
    orient_dfs(0);

    for (int i = 0; i < m; ++i) {
        auto [u, v] = edges[i];
        if (direction[i] == make_pair(u, v)) {
            cout << u + 1 << ' ' << v + 1 << '\n';
        } else {
            cout << v + 1 << ' ' << u + 1 << '\n';
        }
    }

    return 0;
}