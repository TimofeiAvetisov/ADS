#include <bits/stdc++.h>

using namespace std;

vector<set<int>> g;
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
    cin >> n;
    string s;
    cin >> s;
    m = s.size();
    g.resize(n); used.resize(n); match.resize(m, -1);

    for (int i = 0; i < n; ++i) {
        string t;
        cin >> t;
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < 6; ++k) {
                if (s[j] == t[k]) {
                    g[i].insert(j);
                }
            }
        }
    }
    if (n < m) {
        cout << "NO\n";
        return 0;
    }

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        fill(used.begin(), used.end(), false);
        if (khun(i)) {
            cnt++;
        }
    }

    if (cnt < m) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < m; ++i) {
        cout << match[i] + 1 << ' ';
    }
}