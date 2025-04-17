#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    int s, f;
    cin >> s >> f;
    --s;--f;
    vector<vector<pair<int, int>>> g(n);
    vector<int> d(n, INT_MAX), vis(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int tmp;
            cin >> tmp;
            if (tmp == -1 || i == j) {
                continue;
            }
            g[i].emplace_back(j, tmp);
        }
    }


    d[s] = 0;
    for (int i = 0; i < n && !vis[f]; ++i) {
        int v = -1;
        for (int i = 0; i < n; ++i) {
            if (!(vis[i]) && (v == -1 || d[v] > d[i])) {
                v = i;
            }
        }

        vis[v] = true;
        for (auto [u, w] : g[v]) {
            d[u] = min(d[u], d[v] + w);
        }
    }

    if (d[f] == INT_MAX) {
        cout << -1;
        return 0;
    }
    cout << d[f];
}