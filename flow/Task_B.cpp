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
            if ((p =dfs(edge.v, h, min(cnt, edge.cap - edge.flow))) != 0){
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
    cin >> n;
    vector<pair<char, char>> cards(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        cards[i] = {s[0], s[1]};
    }
    string s;
    cin >> s;
    int m = s.size();

    g.assign(n + m + 1 + 1, {}); lvl.assign(n + m + 1 + 1, -1); ptr.assign(n + m + 1 + 1, 0);

    for (int i = 0; i < m; ++i) {
        g[0].push_back({i + 1, (int)g[i + 1].size(), 1, 0});
        g[i + 1].push_back({0, (int)g[0].size() - 1, 0, 0});
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (cards[j].first == s[i] || cards[j].second == s[i]) {
                g[1 + i].push_back({1 + m + j, (int)g[1 + m + j].size(), 1, 0});
                g[1 + m + j].push_back({1 + i, (int)g[1 + i].size() - 1, 0, 0});
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        g[1 + m + j].push_back({n + m + 1, (int)g[n + m + 1].size(), 1, 0});
        g[n + m + 1].push_back({1 + m + j, (int)g[1 + m + j].size() - 1, 0, 0});
        
    }
    int ans = 0;
    while (bfs(0, n + m + 1)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (int flow = dfs(0, n + m + 1, INF)) {
            ans += flow;
        }
    }

    if (ans != m) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> flip(n, 0), match(m, -1);

    for (int i = 0; i < m; ++i) {
        for (auto &e : g[1 + i]) {
            if (e.v >= 1 + m && e.v < 1 + m + n && e.flow > 0) {
                match[i] = e.v - (1 + m);
                flip[e.v - (1 + m)] = (cards[e.v - (1 + m)].first == s[i]) ? 1 : -1;
                break;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        cout << (match[i] + 1) * flip[match[i]] << " ";
    }
    cout << "\n";
}
