#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, rev, cap, flow;
};

const int INF = 1e9;
vector<vector<Edge>> g;
vector<int> lvl, ptr;
int p;


int dfs(int v, int h, int cnt) {
    if (v == h || cnt == 0) {
        return cnt;
    }

    for (int &i = ptr[v]; i < g[v].size(); ++i) {
        auto &edge = g[v][i];
        if (edge.flow < edge.cap && lvl[edge.v] == lvl[v] + 1) {
            if ((p = dfs(edge.v, h, min(cnt, edge.cap - edge.flow))) != 0) {
                edge.flow += p;
                g[edge.v][edge.rev].flow -= p;
                return p;
            }
        }
    }
    return 0;
}

bool bfs(int s, int t) {
    fill(lvl.begin(), lvl.end(), -1);
    queue<int> q;
    lvl[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto &e : g[v]) {
            if (lvl[e.v] == -1 && e.flow < e.cap) {
                lvl[e.v] = lvl[v] + 1;
                q.push(e.v);
            }
        }
    }
    return lvl[t] != -1;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n;
    vector<pair<char, char>> cards(n);
    for (int i = 0; i < n; ++i) {
        cin >> s;
        cards[i] = {s[0], s[1]};
    }
    cin >> s;
    int m = s.size();

    int total = m + n + 27;

    g.assign(total + 1, {}); lvl.assign(total + 1, -1); ptr.assign(total + 1, 0);

    for (int i = 0; i < m; ++i) {
        g[0].push_back({i + 1, (int)g[i + 1].size(), 1, 0});
        g[i + 1].push_back({0, (int)g[0].size() - 1, 0, 0});
    }

    for (int i = 0; i < m; ++i) {
        g[i + 1].push_back({m + 1 + (s[i] - 'a'), (int)g[m + 1 + (s[i] - 'a')].size(), 1, 0});
        g[m + 1 + (s[i] - 'a')].push_back({i + 1, (int)g[i + 1].size() - 1, 0, 0});
    }

    for (int j = 0; j < n; ++j) {
        int normal = m + 1 + (cards[j].first - 'a');
        int flipped = m + 1 + (cards[j].second - 'a');
        g[normal].push_back({m + 27 + j, (int)g[m + 27 + j].size(), 1, 0});
        g[m + 27 + j].push_back({normal, (int)g[normal].size() - 1, 0, 0});
        if (normal != flipped) {
            g[flipped].push_back({m + 27 + j, (int)g[m + 27 + j].size(), 1, 0});
            g[m + 27 + j].push_back({flipped, (int)g[flipped].size() - 1, 0, 0});
        }
    }

    for (int j = 0; j < n; ++j) {
        g[m + 27 + j].push_back({total, (int)g[total].size(), 1, 0});
        g[total].push_back({m + 27 + j, (int)g[m + 27 + j].size() - 1, 0, 0});
    }

    int ans = 0;
    while (bfs(0, total)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (int flow = dfs(0, total, INF)) {
            ans += flow;
        }
    }

    if (ans != m) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> flip(n, 0), match(m, -1);

    vector<vector<int>> used;
    used.resize(26, {});
    for (int c = 0; c < 26; ++c) {
        for (auto &e : g[m + 1 + c]) {
            if (e.v >= m + 27 && e.v < m + 27 + n && e.flow > 0) {
                used[c].push_back(e.v - (m + 27));
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        match[i] = used[s[i] - 'a'].back();
        flip[used[s[i] - 'a'].back()] = (cards[used[s[i] - 'a'].back()].first == s[i]) ? 1 : -1;
        used[s[i] - 'a'].pop_back();
    }

    for (int i = 0; i < m; ++i) {
        cout << (match[i] + 1) * flip[match[i]] << " ";
    }
    cout << "\n";
}
