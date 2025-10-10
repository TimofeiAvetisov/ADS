#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<bool> used;
vector<int> match;

bool khun(int v) {
    if (used[v]) {
        return false;
    }

    used[v] = true;
    for (int u : g[v]) {
        if (match[u] == -1 || khun(match[u])) {
            match[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    g.resize(n); used.resize(n); match.resize(m, -1);
    for (int i = 0; i < n; ++i) {
        int v;
        while ((cin >> v), v != 0) {
            g[i].push_back(v - 1);
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        fill(used.begin(), used.end(), false);
        if (khun(i)) {
            cnt++;
        }
    }

    int ans = 0;
    cout << cnt  << '\n';
    for (int i = 0; i < m; ++i) {
        if (match[i] != -1) {
            cout << match[i] + 1 << ' ' << i + 1 << '\n';
        }
    }
}