#include <bits/stdc++.h>

using namespace std;

int cm = 100;
int day = 1440;
int ma = 3000000;

struct race {
    int t;
    int mm;

    race(int time, int mass) : t(time), mm(mass) {}
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, race>>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v, time, mass;
        cin >> u >> v >> time >> mass;
        --u;--v;mass -= ma;
        g[u].emplace_back(v, race(time, mass));
        g[v].emplace_back(u, race(time, mass));
    }

    int l = 0, r = 1e7 + 1;

    while(l + 1 != r) {
        int mid = (l + r) / 2;
        int curr_mass = cm * mid;
        vector<int> d(n, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        d[0] = 0;
        q.push({0, 0});
        while (!q.empty()) {
            auto [dist, u] = q.top(); q.pop();

            for (auto [v, race] : g[u]) {
                if (race.mm < curr_mass) {
                    continue;
                }

                if (d[v] > d[u] + race.t) {
                    d[v] = d[u] + race.t;
                    if (d[v] > day) {
                        continue;
                    }
                    q.push({d[v], v});
                }
            }
        }

        if (d[n - 1] > day) {
            r = mid;
        } else {
            l = mid;
        }
    } 

    cout << min((int)1e7, l);
}