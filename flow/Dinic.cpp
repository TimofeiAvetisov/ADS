#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, rev, cap, flow;
};

const int INF = 1e9;

vector<vector<Edge>> g;
vector<int> lvl, ptr;
int n, s, t;

void add_edge(int u, int v, int cap) {
    g[u].push_back({v, (int)g[v].size(), cap, 0});
    g[v].push_back({u, (int)g[u].size() - 1, 0, 0});
}

bool bfs() {
    fill(lvl.begin(), lvl.end(), -1);
    queue<int> q;
    lvl[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto &e : g[v]) {
            if (lvl[e.v] == -1 && e.flow < e.cap) {
                lvl[e.v] = lvl[v] + 1;
                q.push(e.v);
            }
        }
    }
    return lvl[t] != -1;
}

int dfs(int v, int pushed) {
    if (v == t || pushed == 0) return pushed;
    for (int &cid = ptr[v]; cid < (int)g[v].size(); ++cid) {
        Edge &e = g[v][cid];
        if (lvl[e.v] != lvl[v] + 1 || e.flow >= e.cap) continue;
        int tr = dfs(e.v, min(pushed, e.cap - e.flow));
        if (tr == 0) continue;
        e.flow += tr;
        g[e.v][e.rev].flow -= tr;
        return tr;
    }
    return 0;
}

int dinic() {
    int flow = 0;
    while (bfs()) {
        fill(ptr.begin(), ptr.end(), 0);
        while (int pushed = dfs(s, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m >> s >> t;
    --s; --t;

    g.assign(n, {});
    lvl.resize(n);
    ptr.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        --u; --v;
        add_edge(u, v, c);
    }

    cout << dinic() << '\n';
}
