#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

struct point {
    point(int x, int y) : x(x), y(y) {}
    point() : x(0), y(0) {}
    int x, y;
};

istream& operator>>(istream& in, point& p) {
    return in >> p.x >> p.y;
}

double find_dist(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n;
    cin >> n;
    vector<point> points(n);

    for (int i = 0; i < n; ++i) {
        cin >> points[i];
    }

    int m;
    cin >> m;
    vector<vector<double>> g(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i][j] = find_dist(points[i], points[j]);
        }
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;--b;
        g[a][b] = 0;
        g[b][a] = 0;
    }

    set<pair<double, int>> q;
    q.insert({0.0, 0});
    double answer = 0;
    vector<double> dist(n, DBL_MAX);
    dist[0] = 0;
    vector<bool> vis(n, false);

    while(!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());

        if(vis[u]) continue;

        vis[u] = true;
        answer += dist[u];
        for (int v = 0; v < n; ++v) {
            double w = g[u][v];
            if (w < dist[v]) {
                q.erase({dist[v], v});
                dist[v] = w;
                q.insert({dist[v], v});
            }
        }
    }

    cout << fixed << setprecision(5) << answer;
}