#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> tin, fup, answer, smallest_path, parent;
vector<bool> used, is_cutpoint;
int timer = 0, finish, s;

void dfs(int v, int p) {
    used[v] = true;
    parent[v] = p;
    tin[v] = fup[v] = timer++;
    int child = 0;
    for (auto u : g[v]) {
        if (u == p) continue;
        if (used[u]) {
            fup[v] = min(fup[v], tin[u]);
        } else {
            dfs(u, v);
            fup[v] = min(fup[v], fup[u]);
            if (fup[u] >= tin[v] && p != -1) {
                    is_cutpoint[v] = true;
            }
            child++;
        }
    }
    if (p == -1 && child > 1) {
        is_cutpoint[v] = true;
    }
}

bool dfs(int v) {
    used[v] = true;
    bool returned = false;
    for (auto u : g[v]) {
        if (!used[u]) {
            returned = returned || dfs(u);
        }
    }
    if (returned && is_cutpoint[v] && v != s && v != finish) {
        answer.push_back(v + 1);
    }
    return returned || (v == finish);
}

int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n);tin.resize(n);fup.resize(n);used.resize(n);is_cutpoint.resize(n);parent.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> s >> finish;
    s--;finish--;
    dfs(s, -1);
    used.assign(n, false);
    dfs(s);

    int fc = finish;
    while(parent[fc] != -1) {
        fc = parent[fc];
        smallest_path.push_back(fc);
    }
    used.assign(n, false);
    for (auto q : smallest_path) {
        used[q] = true;
    }

    int cnt = 0;
    vector<int> final_answer;
    for (auto q : answer) {
        if (used[q]) {
            cnt++;
            final_answer.push_back(q);
        }
    }
    cout << final_answer.size() << '\n';
    sort(final_answer.begin(), final_answer.end());



    for (auto a : final_answer) {
        cout << a << '\n';
    }

}
