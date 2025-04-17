#include <bits/stdc++.h>
using namespace std;

int timer; 
vector<vector<int>> g;
vector<int> tin, tup, pr;
vector<bool> vis, contains_v, ans;
int s, finish;

void dfs(int u) {
    vis[u] = true;
    tin[u] = tup[u] = ++timer;
    contains_v[u] = (u == finish);
    
    for (int v : g[u]) {
        if (!vis[v]) {
            pr[v] = u;
            dfs(v);
            contains_v[u] = contains_v[u] || contains_v[v];
            tup[u] = min(tup[u], tup[v]);
            if (u != s && contains_v[v] && tup[v] >= tin[u])
                ans[u] = true;
        }
        else if (v != pr[u]) {
            tup[u] = min(tup[u], tin[v]);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    g.assign(n, vector<int>());
    tin.assign(n, 0);
    tup.assign(n, 0);
    pr.assign(n, -1);
    vis.assign(n, false);
    contains_v.assign(n, false);
    ans.assign(n, false);
    
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    cin >> s >> finish;
    --s; --finish;
    timer = 0;
    dfs(s);
    
    vector<int> answer;
    for (int u = 0; u < n; u++){
        if (u == s || u == finish) continue;
        if (ans[u])
            answer.push_back(u);
    }
    
    sort(answer.begin(), answer.end());
    
    cout << answer.size() << "\n";
    for (int a : answer) {
        cout << a + 1 << "\n";
    }
    
    return 0;
}
