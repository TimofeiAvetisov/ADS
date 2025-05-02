#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> tr(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int q;
            cin >> q;
            tr[i][j] = q;
        }
    }

    for (int p = 0; p < n; ++p) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                tr[u][v] = min(tr[u][v], tr[u][p] + tr[p][v]);
            }
        }
    }

    int maxi = -1;
    for (auto q : tr) {
        for (auto p : q) {
            maxi = max(maxi, p);
        }
    }
    cout << maxi;
}