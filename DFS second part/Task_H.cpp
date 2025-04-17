#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    priority_queue<int> minheap;
    vector<int> deg(n, 0);

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v;
            --v;
            g[i].push_back(v);
            deg[v] += 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (deg[i] == 0) {
            minheap.push(i);
        }
    }
    vector<int> answer;
    while(!minheap.empty()) {
        int u = minheap.top(); minheap.pop();

        answer.push_back(u);

        for (auto v : g[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                minheap.push(v);
            }
        }
    }

    reverse(answer.begin(), answer.end());
    for (auto q : answer) {
        cout << q + 1 << ' ';
    }

    cout << '\n';
}