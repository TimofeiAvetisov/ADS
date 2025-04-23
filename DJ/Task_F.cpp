#include <bits/stdc++.h>

using namespace std;

#define int long long

struct race {
    int dep;
    int arr;

    race(int departure, int arrival) : dep(departure), arr(arrival) {}
};

signed main() {
    int n;
    cin >> n;
    int s, t;
    cin >> s >> t;
    --s;--t;
    int r;
    cin >> r;

    vector<vector<pair<int, race>>> g(n);
    for (int i = 0; i < r; ++i) {
        int u, v, dep, arr;
        cin >> u >> dep >> v >> arr;
        --u;--v;
        g[u].emplace_back(v, race(dep, arr));
    }

    vector<int> d(n, LONG_LONG_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, s});
    d[s] = 0;
    while(!q.empty()) {
        auto [dist, v] = q.top(); q.pop();
        for (auto [u, r] : g[v]) {
            if (r.dep < dist) {
                continue;
            }
            if (r.arr < d[u]) {
                d[u] = r.arr;
                q.push({d[u], u});
            }
        }
    }

    cout << (d[t] == LONG_LONG_MAX ? -1 : d[t]);


}