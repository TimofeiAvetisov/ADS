#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, rev, cap, flow;
};

const int INF = 1e9;
vector<vector<Edge>> g;
vector<int> lvl, ptr;
int p;

int dfs(int v, int h, int cnt) {
    if (v == h || cnt == 0) {
        return cnt;
    }

    for (int &i = ptr[v]; i < g[v].size(); ++i) {
        auto &edge = g[v][i];
        if (edge.flow < edge.cap && lvl[edge.v] == lvl[v] + 1) {
            if ((p =dfs(edge.v, h, min(cnt, edge.cap - edge.flow))) != 0){
                edge.flow += p;
                g[edge.v][edge.rev].flow -= p;
                return p;
            }
        }

    }
    return 0;
}

bool bfs(int a, int h) {
    fill(lvl.begin(), lvl.end(), -1);
    queue<int> q;
    lvl[a] = 0;
    q.push(a);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto &edge : g[v]) {
            if (lvl[edge.v] == -1 && edge.flow < edge.cap) {
                lvl[edge.v] = lvl[v] + 1;
                q.push(edge.v);
            }
        }
    }
    return lvl[h] != -1;
}


bool dfs2(int v, int h, vector<int> &path) {
    path.push_back(v);
    if (v == h) {
        return true;
    }
    for (auto &edge : g[v]) {
        if (edge.flow > 0) {
            edge.flow -= 1;
            if (dfs2(edge.v, h, path))
                return true;
            edge.flow += 1;
        }
    }
    path.pop_back();
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, h;
    cin >> n >> m >> a >> h;
    --a; --h;

    g.assign(n, {});
    lvl.assign(n, -1);
    ptr.assign(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back({v, (int)g[v].size(), 1, 0});
        g[v].push_back({u, (int)g[u].size() - 1, 0, 0});
    }

    int ans = 0;
    while (bfs(a, h)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (int flow = dfs(a, h, INF)) {
            ans += flow;
        }
    }

    if (ans < 2) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    vector<int> path1, path2;
    dfs2(a, h, path1);
    dfs2(a, h, path2);

    for (int v : path2){
         cout << v + 1 << ' ';
    }
    cout << '\n';
    for (int v : path1) {
        cout << v + 1 << ' ';
    }
    cout << '\n';
}
