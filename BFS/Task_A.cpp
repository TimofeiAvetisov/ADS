#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int tmp;
            cin >> tmp;
            if(tmp) {
                g[i].push_back(j);
            }
        }
    }
    int a, b;
    cin >> a >> b;
    --a;--b;

    int start = 0, end = 1;
    vector<int> q(2 * n), d(n, -1);
    d[a] = 0;
    q[start] = a;
    while (start != end && d[b] == -1) {
        int v = q[start];
        start++;
        for (auto u : g[v]) {
            if (d[u] == -1) {
                q[end] = u;
                d[u] = d[v] + 1;
                ++end;
            }
        }
    }
    cout << d[b];
}