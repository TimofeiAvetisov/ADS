#include <bits/stdc++.h>

using namespace std;
#define int long long

vector<int> d;
vector<vector<int>> g, p;
int L = 20;

void dfs(int v, int pr)
{
    d[v] = d[pr] + 1;
    p[v][0] = pr;
    for(int i = 1; i < L; ++i){
        p[v][i] = p[p[v][i - 1]][i - 1];
    }
    for(auto i : g[v]){
        dfs(i, v);
    }
}

int lca(int a, int b) {
    if (d[a] < d[b])
        swap(a, b);
    int x = d[a] - d[b];
    for (int i = 0; i < L; ++i)
    {
        if((x >> i) & 1)
        {
            a = p[a][i];
        }
    }
    if(a == b)
        return a;
    for(int i = L - 1; i >= 0; --i)
    {
        if(p[a][i] != p[b][i])
        {
            a = p[a][i];
            b = p[b][i];
        }
    }
    return p[a][0];
}


signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    g.resize(n);
    p.resize(n, vector<int>(L));
    d.resize(n);

    for (int i = 1; i < n; ++i) {
        int pr;
        cin >> pr;
        g[pr].push_back(i);
    }

    dfs(0, 0);

    long long answer = 0;
    int a, b;
    cin >> a >> b;
    int x, y, z;
    cin >> x >> y >> z;
    int ans;

    for (int i = 0; i < m; ++i) {
        if (i == 0) {
            ans = lca(a, b);
        } else {
            ans = lca((a + ans) % n, b);
        }
        answer += ans;
        a = (x * a + y * b + z) % n;
        b = (x * b + y * a + z) % n;
    }

    cout << answer;
}