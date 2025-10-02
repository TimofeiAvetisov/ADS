#include <bits/stdc++.h>

using namespace std;
#define int long long

vector<int> d;
vector<vector<int>> p, q;
vector<vector<pair<int, int>>> g;
int L = 20;

void dfs(int v, int pr, int edge_sz)
{
    d[v] = d[pr] + 1;
    p[v][0] = pr;
    q[v][0] = edge_sz;
    for(int i = 1; i < L; ++i){
        p[v][i] = p[p[v][i - 1]][i - 1];
        q[v][i] = min(q[v][i - 1],  q[p[v][i - 1]][i - 1]);
    }
    for(auto [i, sz] : g[v]){
        dfs(i, v, sz);
    }
}

int lca(int a, int b) {
    int answer = 1e9;
    if (d[a] < d[b])
        swap(a, b);
    int x = d[a] - d[b];
    for (int i = 0; i < L; ++i) {
        if((x >> i) & 1) {
            answer = min(answer, q[a][i]);
            a = p[a][i];
        }
    }
    if(a == b)
        return answer;
    for(int i = L - 1; i >= 0; --i)
    {
        if(p[a][i] != p[b][i])
        {   
            answer = min(answer, min(q[a][i], q[b][i]));
            a = p[a][i];
            b = p[b][i];
        }
    }
    return min(answer, min(q[a][0], q[b][0]));
}


signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n;
    g.resize(n);
    p.resize(n, vector<int>(L)); q.resize(n, vector<int>(L, 1e9));
    d.resize(n);

    for (int i = 1; i < n; ++i) {
        int pr, w;
        cin >> pr >> w;
        --pr;
        g[pr].emplace_back(i, w);
    }

    dfs(0, 0, 1e9);

    cin >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;
        cout << lca(u, v) << '\n';
    }
}