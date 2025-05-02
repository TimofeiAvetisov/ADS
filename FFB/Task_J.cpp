#include <bits/stdc++.h>

using namespace std;

#define int long long

const long long INF = LONG_LONG_MAX;

struct edge {
    edge(int from, int to, int w) : from(from), to(to), w(w)
    {}
    int from, to, w;
};

void find_cycle(int v, int n, vector<int>& pr, vector<bool>& vis) {
    int inpt = v;
    for (int i = 0; i < n; ++i) {
        v = pr[v];
    }

    int cur = v;
    if (vis[v]) {
        return;
    }

    
    vis[v] = true;
    cur = pr[v];
    while (cur != v) {
        vis[cur] = true;
        cur = pr[cur];
    }

}

signed main() {
    int n, m;
    cin >> n >> m;

    vector<edge> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;--v;
        edges.emplace_back(u, v, -w);
    }

    vector<int> d(n, INF), pr(n, -1);

    d[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (auto edge : edges) {
            if (d[edge.from] != INF && d[edge.to] > d[edge.from] + edge.w) {
                d[edge.to] = d[edge.from] + edge.w;
                pr[edge.to] = edge.from;
            }
        }
    }

    if (d[n - 1] == INF) {
        cout << ":(";
        return 0;
    }

    vector<bool> in_cycle(n, false);
    for (auto edge : edges) {
        if (d[edge.from] != INF && d[edge.to] > d[edge.from] + edge.w) {
            find_cycle(edge.to, n, pr, in_cycle);
        }
    }

    vector<vector<int>> g(n);
    for (auto edge : edges) {
        g[edge.from].push_back(edge.to);
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_cycle[i]) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int u = q.front();q.pop();
        for (auto v : g[u]) {
            if (!in_cycle[v]) {
                in_cycle[v] = true;
                q.push(v);
            }
        }
    }

    if (in_cycle[n - 1]) {
        cout << ":)";
        return 0;
    }

    cout << -d[n - 1];
}