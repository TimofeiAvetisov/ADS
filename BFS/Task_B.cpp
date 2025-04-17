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
            if (tmp) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    int a, b;
    cin >> a >> b;
    --a;--b;

    if (a == b) {
        cout << 0;
        return 0;
    }

    vector<int> q(2 * n), pr(n, 0), dist(n, -1);
    int start = 0;
    int end = 1;

    pr[a] = -1;
    dist[a] = 0;
    q[0] = a; 

    while (dist[b] == -1 && end != start) {
        int u = q[start];
        ++start;

        for (auto v : g[u]) {
            if (dist[v] == -1) {
                q[end] = v;
                ++end;
                dist[v] = dist[u] + 1;
                pr[v] = u;
            }
        }
    }

    if (dist[b] == -1) {
        cout << -1;
        return 0;
    }

    cout << dist[b] << '\n';

    vector<int> answer;
    while (pr[b] != -1) {
        answer.push_back(b + 1);
        b = pr[b];
    }
    answer.push_back(a + 1);
    reverse(answer.begin(), answer.end());

    for (auto a : answer) {
        cout << a << ' ';
    }
}