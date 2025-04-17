#include <bits/stdc++.h>
using namespace std;

vector<vector<double>> g;
vector<pair<int, int>> v;
vector<int> clr;

double dist(pair<int, int> a, pair<int, int> b) {
    double dx = a.first - b.first;
    double dy = a.second - b.second;
    return sqrt(dx * dx + dy * dy);
}

bool dfs(int v, int c, double max_dist) {
    clr[v] = c;
    for (int u = 0; u < g[v].size(); ++u) {
        if (g[v][u] < max_dist + 1e-9 && g[v][u] != 0) {
            if (clr[u] == 0) {
                if (!dfs(u, 3 - c, max_dist)) {
                    return false;
                }
            } else if (clr[u] == c) {
                return false;
            }
        }
    }
    return true;
}

bool try_clr(double R, int n) {
    clr.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        if (clr[i] == 0) {
            if (!dfs(i, 1, 2 * R)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    v.resize(n);
    clr.resize(n);
    g.resize(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        v[i] = {x, y};
    }

    double max_d = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i][j] = dist(v[i], v[j]);
            if (g[i][j] > max_d) {
                max_d = g[i][j];
            }
        }
    }

    double l = 0, r = 1e6;
    double best_R = 0;
    vector<int> best_coloring(n, 1);

    for (int iter = 0; iter < 100; ++iter) {
        double mid = (l + r) / 2;
        if (try_clr(mid, n)) {
            best_R = mid;
            best_coloring = clr;
            l = mid;
        } else {
            r = mid;
        }
    }

    cout << fixed << setprecision(15) << best_R << endl;
    for (int c : best_coloring) {
        cout << c << ' ';
    }
    cout << '\n';
}
