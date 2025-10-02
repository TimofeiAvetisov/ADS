#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MOD = 1e9 + 7;
int k;

unordered_map<char, int> mp;

struct Node {
    vector<int> to, next;
    int link, term;
    bool is_terminal;

    Node() : to(k, -1), next(k, -1), link(-1), term(-1), is_terminal(false) {}

};
vector<Node> ah;


void add_string(const string &s) {
    int cur = 0;
    for (auto c : s) {
        int i = mp[c];
        if (ah[cur].to[i] == -1) {
            ah[cur].to[i] = ah.size();
            ah.emplace_back();
        }

        cur = ah[cur].to[i];
    }
    ah[cur].is_terminal = true;
}

void build() {
    queue<int> q;
    ah[0].link = 0;

    for (int c = 0; c < k; ++c) {
        int v = ah[0].to[c];
        if (v != -1) {
            ah[0].next[c] = v;
            ah[v].link = 0;
            ah[v].term = -1;
            q.push(v);
        } else {
            ah[0].next[c] = 0;
        }
    }

    while (!q.empty()) {
        int v = q.front();q.pop();

        for (int c = 0; c < k; ++c) {
            int u = ah[v].to[c];
            if (u != -1) {
                ah[v].next[c] = u;
                ah[u].link = ah[ah[v].link].next[c];
                ah[u].term = (ah[ah[u].link].is_terminal ? ah[u].link : ah[ah[u].link].term);

                q.push(u);
            } else {
                ah[v].next[c] = ah[ah[v].link].next[c];
            }
        }
    }
}

inline bool is_bad(int v) {
    return ah[v].is_terminal || ah[v].term != -1;
}

void solve(int m) {
    vector<vector<int>> dp(m + 1, vector<int>(ah.size(), 0));
    dp[0][0] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < (int)ah.size(); j++) {
            if (dp[i][j] == 0 || is_bad(j)) continue;
            for (int c = 0; c < k; c++) {
                int u = ah[j].next[c];
                if (!is_bad(u)) {
                    dp[i + 1][u] = (dp[i + 1][u] + dp[i][j]) % MOD;
                }
            }
        }
    }

    int ans = 0;
    for (int v = 0; v < (int)ah.size(); v++) {
        if (!is_bad(v)) {
            ans = (ans + dp[m][v]) % MOD;
        }
    }
    cout << ans << "\n";
}


signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m, p;
    cin >> k >> m >> p;
    ah.emplace_back();
    string alph;
    cin >> alph;
    for (int i = 0; i < k; ++i) {
        mp[alph[i]] = i;
    }
    for (int i = 0; i < p; ++i) {
        string tmp;
        cin >> tmp;
        add_string(tmp);
    }
    build();
    solve(m);
    
}