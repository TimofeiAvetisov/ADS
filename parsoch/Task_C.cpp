#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<bool> used;
vector<int> match;
vector<vector<int>> g_dop;

bool khun(int v) {
    if (used[v]) {
        return false;
    }

    used[v] = true;
    for (int u : g_dop[v]) {
        if (match[u] == -1 || khun(match[u])) {
            match[u] = v;
            return true;
        }
    }
    return false;
}


void dfs(int v, vector<bool> &visL, vector<bool> &visR) {
    visL[v] = true;
    for (int u : g_dop[v]) {
        if (match[u] == v) continue;
        if (!visR[u]) {
            visR[u] = true;
            if (match[u] != -1 && !visL[match[u]]) {
                dfs(match[u], visL, visR);
            }
        }
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    g.clear(); used.clear(); match.clear();g_dop.clear();
    g.resize(n); used.resize(n); match.resize(m, -1);g_dop.resize(n);
     

    for (int i = 0; i < n; ++i) {
        int v;
        while ((cin >> v), v != 0) {
            g[i].push_back(v - 1);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (find(g[i].begin(), g[i].end(), j) == g[i].end()) {
                g_dop[i].push_back(j);
            }
        }
    }




    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        fill(used.begin(), used.end(), false);
        if (khun(i)) {
            cnt++;
        }
    }

    vector<bool> visL(n, false), visR(m, false);

    for (int i = 0; i < n; ++i) {
        bool matched = false;
        for (int j = 0; j < m; ++j) {
            if (match[j] == i) {
                matched = true;
                break;
            }
        }
        if (!matched) dfs(i, visL, visR);
    }

    vector<int> b_ans, g_ans;
    for (int i = 0; i < n; ++i) {
        if (visL[i]) b_ans.push_back(i);
    }
    for (int j = 0; j < m; ++j) {
        if (!visR[j]) g_ans.push_back(j);
    }

    cout << b_ans.size() + g_ans.size() << '\n';
    cout << b_ans.size() << ' ' << g_ans.size() << '\n';
    for (int b : b_ans) {
        cout << b + 1 << ' ';
    }
    cout << '\n';
    for (int g : g_ans) { 
        cout << g + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        solve();
    }
}