#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<vector<int>> g, g_t;
vector<int> top_sort, time_req;
vector<bool> vis;
int cnt = 0, timer = 0;;

void Top_sort(int u) {
    if (vis[u]) {
        return;
    }

    vis[u] = true;
    for (auto v : g[u]) {
        Top_sort(v);
    }
    top_sort.push_back(u);
}

void dfs(int u) {
    if (vis[u]) return;

    vis[u] = true;
    cnt += 1;
    timer += time_req[u];
    for (auto v : g_t[u]) {
        dfs(v);
    }
}

signed main() {
    int n;
    cin >> n;
    g.resize(n); g_t.resize(n);
    vis.resize(n, false); time_req.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> time_req[i];
    }
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {    
            int u;
            cin >> u;
            --u;

            g[u].push_back(i);
            g_t[i].push_back(u);   
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            Top_sort(i);
        }
    }

    reverse(top_sort.begin(), top_sort.end());

    vis.assign(n, false);
    dfs(0);

    cout << timer << ' ' << cnt << '\n';

    for (auto q : top_sort) {
        if (vis[q]) {
            cout << q + 1 << ' ';
        }
    }
    cout << '\n';
}