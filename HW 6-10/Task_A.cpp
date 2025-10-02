#include <bits/stdc++.h>

using namespace std;

vector<int> p, s;

int leader(int v) {
    return (p[v] == v) ? v : p[v] = leader(p[v]);
}

void unite(int a, int b) {
    a = leader(a), b = leader(b);
    if (s[a] > s[b])
        swap(a, b);
    s[b] += s[a];
    p[a] = b;
}

void init(int n) {
    p.resize(n); s.resize(n);
    for (int i = 0; i < n; i++)
        p[i] = i, s[i] = 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, pair<int, int>>> oper(k);
    init(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
    }

    for (int i = 0; i < k; ++i) {
        char cmd;
        cin >> cmd;
        cin >> cmd;
        cin >> cmd;
        int u, v;
        cin >> u >> v;
        if (cmd == 'k') {
            oper[i] = {0, {u, v}};
        } else {
            oper[i] = {1, {u, v}};
        }
    }

    reverse(oper.begin(), oper.end());
    vector<bool> answers;
    

    for (auto [cmd, q] : oper) {
        auto [u, v] = q;
        --u;--v;
        if (cmd == 1) {
            unite(u, v);
        } else {
            if (leader(u) != leader(v)) {
                answers.push_back(false);
            } else {
                answers.push_back(true);
            }
        }
    }

    reverse(answers.begin(), answers.end());

    for (auto q : answers) {
        if (q) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}