#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<double>> tr(n, vector<double>(n, 2));
    int s, e;
    cin >> s >> e;
    --s;--e;
    for (int i = 0; i < m; ++i) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        --u;--v;
        w /= 100;
        tr[u][v] = w;
        tr[v][u] = w;
    }

    for (int p = 0; p < n; ++p) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (tr[u][v] == 2) {
                    if (tr[u][p] == 2 || tr[p][v] == 2) {
                        tr[u][v] = 2;
                    } else {
                        tr[u][v] = tr[u][p] + tr[p][v] - tr[u][p] * tr[p][v];
                    }
                } else {
                    if (tr[u][p] != 2 && tr[p][v] != 2) {
                        tr[u][v] = min(tr[u][v], tr[u][p] + tr[p][v] - tr[u][p] * tr[p][v]);
                    }
                }
            }
        }
    }

    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(3) << tr[s][e];
}