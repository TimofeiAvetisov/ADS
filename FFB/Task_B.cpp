#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<bool>> tr(n, vector<bool>(n, false));

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
                tr[u][v] = tr[u][v] || (tr[u][p] && tr[p][v]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (tr[i][i]) {
            cout << 1;
            return 0;
        }
    }
    cout << 0;
}