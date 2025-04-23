#include <bits/stdc++.h>

using namespace std;

struct race {
    long long dep;
    long long arr;

    race(long long departure, long long arrival) : dep(departure), arr(arrival) {}
};

vector<vector<pair<long long, race>>> g;
vector<int> points;

long long dj(int start, long long start_dist, int n, int finish) {
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> q;
    vector<long long> d(n, LONG_LONG_MAX);
    if (start_dist == LONG_LONG_MAX) {
        return LONG_LONG_MAX;
    }
    d[start] = start_dist;
    q.push({start_dist, start});
    while(!q.empty()) {
        auto [dist, u] = q.top(); q.pop();

        for (auto [v, r] : g[u]) {
            long long dep_time = ((dist + r.dep - 1) / r.dep) * r.dep;
            if ((dep_time + r.arr) < d[v]) {
                d[v] = dep_time + r.arr;
                q.push({d[v], v});
            }
        }
    }

    return d[finish];
}

int main() {
    long long n, k;
    cin >> n >> k;
    g.resize(n);
    for (long long i = 0; i < k; ++i) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        --a;--b;
        g[a].emplace_back(b, race(c, d));
    }
    long long m;
    cin >> m;
    points.resize(m);
    for (long long i = 0; i < m; ++i) {
        cin >> points[i];
        --points[i];
    }
    long long dist = dj(points[0], 0, n, points[1]);
    for (int i = 1; i < m - 1; ++i) {
        if (dist == LONG_LONG_MAX) {
            cout << -1;
            return 1;
        }
        dist = dj(points[i], dist, n, points[i + 1]);
    }

    if (dist == LONG_LONG_MAX) {
        cout << -1;
        return 0;
    }

    cout << dist;
}