#include <bits/stdc++.h>

using namespace std;

#define int long long

const long long INF = LONG_LONG_MAX;

struct edge {
    edge(int from, int to, int w) : from(from), to(to), w(w)
    {}
    int from, to, w;
};

signed main() {
    int n;
    cin >> n;
    
    vector<edge> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w;
            cin >> w;
            if (w != 1e5) {
                edges.emplace_back(i, j, w);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        edges.emplace_back(n, i, 0);
    } 

    vector<int> d(n + 1, INF), pr(n + 1, -1);

    d[n] = 0;
    for (int i = 0; i < n; ++i) {
        for (auto edge : edges) {
            if (d[edge.from] != INF && d[edge.to] > d[edge.from] + edge.w) {
                d[edge.to] = d[edge.from] + edge.w;
                pr[edge.to] = edge.from;
            }
        }
    }

    int v = -1;
    for (auto edge : edges) {
        if (d[edge.to] > d[edge.from] + edge.w) {
            v = edge.to;
            break;
        }
    }

    if (v == -1) {
        cout << "NO";
        return 0;
    }


    for (int i = 0; i < n; ++i) {
        v = pr[v];
    }
    int cur = v;
    vector<int> cycle;
    cycle.push_back(v);
    cur = pr[v];
    while (cur != v) {
        cycle.push_back(cur);
        cur = pr[cur];
    }

    cycle.push_back(cur);

    reverse(cycle.begin(), cycle.end());

    cout << "YES\n";
    cout << cycle.size() << '\n';
    for (auto q : cycle) {
        cout << q + 1 << ' ';
    }
}