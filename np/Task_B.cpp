#include <bits/stdc++.h>

using namespace std;

vector<int> scc(const vector<vector<int>>& g, const vector<vector<int>>& g_rev) {
    int n = g.size();
    vector<bool> used(n, false);
    vector<int> order;
    order.reserve(n);
    vector<pair<int, int>> que;
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            continue;
        }
        que.push_back({i, 0});
        used[i] = true;
        while (!que.empty()) {
            int u = que.back().first;
            int &idx = que.back().second;
            if (idx < static_cast<int>(g[u].size())) {
                int v = g[u][idx++];
                if (!used[v]) {
                    used[v] = true;
                    que.push_back({v, 0});
                }
            } else {
                order.push_back(u);
                que.pop_back();
            }
        }
    }

    vector<int> comp(n, -1);
    vector<int> stack;
    stack.reserve(n);
    int cur = 0;
    for (int i = n - 1; i >= 0; --i) {
        int v = order[i];
        if (comp[v] != -1) {
            continue;
        }
        stack.push_back(v);
        comp[v] = cur;
        while (!stack.empty()) {
            int ind = stack.back();
            stack.pop_back();
            for (int u : g_rev[ind]) {
                if (comp[u] == -1) {
                    comp[u] = cur;
                    stack.push_back(u);
                }
            }
        }
        ++cur;
    }

    return comp;
}

int char_int(char clr) {
    return clr == 'R' ? 0 : (clr == 'G' ? 1 : 2);
}

char int_char(int ind) {
    return "RGB"[ind];
}

void add_edge(int u, int v, vector<vector<int>>& g, vector<vector<int>>& g_rev) {
    g[u ^ 1].push_back(v);
    g_rev[v].push_back(u ^ 1);
    g[v ^ 1].push_back(u);
    g_rev[u].push_back(v ^ 1);
}

int make_val(int v, int boolian) {
    return ((v * 2) | boolian);
}

int clr_ind(int v, int clr, vector<int>& clr1, vector<int>& clr2) {
    if (clr1[v] == clr) return 0;
    if (clr2[v] == clr) return 1;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    string s;
    cin >> n >> m >> s;

    vector<int> clr1(n), clr2(n);
    for (int i = 0; i < n; ++i) {
        int c = char_int(s[i]);
        if (c == 0) {
            clr1[i] = 1; clr2[i] = 2;
        }
        else if (c == 1) {
            clr1[i] = 0; clr2[i] = 2;
        }
        else {
            clr1[i] = 0; clr2[i] = 1;
        }
    }

    vector<vector<int>> g(2 * n), g_rev(2 * n);


    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        for (int c = 0; c < 3; ++c) {
            int pos_u = clr_ind(u, c, clr1, clr2), pos_v = clr_ind(v, c, clr1, clr2);
            if (pos_u != -1 && pos_v != -1) {
                add_edge(make_val(u, 1 - pos_u), make_val(v, 1 - pos_v), g, g_rev);
            }
        }
    }

    vector<int> cmp = scc(g, g_rev);

    string answer(n, '\0');
    for (int v = 0; v < n; ++v) {
        if (cmp[2 * v] == cmp[2 * v + 1]) {
            cout << "Impossible\n";
            return 0;
        }
        answer[v] = int_char((cmp[2 * v] > cmp[2 * v + 1] ? clr1[v] : clr2[v])); // если че инвертнуть условие
    }
    cout << answer << '\n';
}
