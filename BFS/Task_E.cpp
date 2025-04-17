#include <bits/stdc++.h>
using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

pair<int, int> form_edge(int a, int b) {
    return make_pair(max(a, b), min(a, b));
}

int main() {
    int n, m;
    cin >> n >> m;
    unordered_map<pair<int, int>, pair<bool, int>, PairHash> edges;
    vector<vector<int>> g(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        auto edge = form_edge(u, v);
        edges[edge] = {true, edges[edge].second + 1};
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int s, t;
    cin >> s >> t;
    --s; --t;

    vector<int> dist(n, -1);
    vector<vector<int>> pr(n);
    vector<int> q(2 * n);
    q[0] = s;
    dist[s] = 0;
    pr[s] = {-1};
    int start = 0, end = 1;

    while (start != end) {
        int v = q[start++];
        for (int u : g[v]) {
            if (dist[u] == -1 || dist[u] == dist[v] + 1) {
                if (dist[u] == -1) {
                    q[end++] = u;
                }
                pr[u].push_back(v);
                dist[u] = dist[v] + 1;
            }
        }
    }

    vector<bool> vis(n, false);
    vector<int> q2(2 * n);
    q2[0] = t;
    vis[t] = true;
    start = 0, end = 1;

    while (start != end) {
        int v = q2[start++];
        for (int u : pr[v]) {
            if (u == -1) continue;
            if (!vis[u]) {
                q2[end++] = u;
                vis[u] = true;
            }
            edges[form_edge(u, v)].first = false;

        }
    }

    int answer = 0;
    for (auto& [edge, xd] : edges) {
        if (xd.first) {
            answer += xd.second;
        }
    }

    cout << answer;
    return 0;
}