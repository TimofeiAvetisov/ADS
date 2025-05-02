#include <bits/stdc++.h>

using namespace std;

#define int long long

struct edge {
    edge(int from, int dep, int to, int arr) : from(from), dep(dep), to(to), arr(arr)
    {}
    int from, dep, to, arr;
};

signed main() {
    int n;
    cin >> n;
    int s, f;
    cin >> s >> f;
    --s;--f;

    int m;
    cin >> m;
    vector<edge> edges;
    edges.reserve(m);
    
    for (int i = 0; i < m; ++i) {
        int u, d, v, a;
        cin >> u >> d >> v >> a;
        --u;--v;
        edges.emplace_back(u, d, v, a);
    }

    vector<int> d(n, LONG_LONG_MAX);
    d[s] = 0;
    for (int i = 0; i < m; ++i) {
        for (auto edge : edges) {
            if (d[edge.from] <= edge.dep) {
                d[edge.to] = min(d[edge.to], edge.arr);
            }
        }
    }

    cout << d[f];
}