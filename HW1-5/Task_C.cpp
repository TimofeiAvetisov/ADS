#include <bits/stdc++.h>

using namespace std;


int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    pair<int, int> s, f;

    vector<vector<int>> g(n + 2, vector<int>(m + 2, 0));

    for (int i = 0; i < n + 2; ++i) {
        for (int j = 0; j < m + 2; ++j) {
            if (j == 0 || j == m + 1 || i == 0 || i == n + 1) {
                g[i][j] = 1;
                continue;
            }
            char t;
            cin >> t;
            if (t == 'S') {
                s = {i, j};
            }
            if (t == 'F') {
                g[i][j] = 2;
            }

            if (t == 'P') {
                g[i][j] = 1;
            }
        }
    }


    vector<pair<int, int>> q(4 * n * m);
    vector<vector<int>> dist(n + 2, vector<int>(m + 2, -1));
    int answer = 1e9;
    int start = 0, end = 1;
    q[0] = s;
    dist[s.first][s.second] = 0;

    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while(start != end) {
        auto pos = q[start++];
        for (auto dir : dirs) {
            auto cpos = pos;
            while(g[cpos.first + dir.first][cpos.second + dir.second] != 1) {
                cpos.first += dir.first; cpos.second += dir.second;
                if (g[cpos.first][cpos.second] == 2) {
                    cout << dist[pos.first][pos.second] + 1;
                    return 0;
                }

                int d = dist[cpos.first][cpos.second]; 
                if (d == -1 || d > dist[pos.first][pos.second] + 1) {
                    dist[cpos.first][cpos.second] = dist[pos.first][pos.second] + 1;
                    q[end++] = cpos;
                }
            }
        }
    }

    cout << -1;
}