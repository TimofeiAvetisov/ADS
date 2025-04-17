#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, s, t, q;
    cin >> n >> m >> s >> t >> q;
    --s; --t;
    vector<vector<int>> g(n, vector<int>(m, 0));
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        g[x][y] = 1;
    }

    vector<pair<int, int>> qu(n * m * 8);
    qu[0] = {s, t};
    vector<vector<int>> dist(n, vector<int>(m, -1));
    dist[s][t] = 0;
    int start = 0, end = 1;
    
    vector<pair<int, int>> moves = {
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}
    };

    int cnt_q = 0, dist_sum = 0;
    bool all_reached = false;

    if (g[s][t] == 1) {
        cnt_q++;
    }

    while (start != end) {
        auto [x, y] = qu[start];
        ++start;

        for (auto [move_x, move_y] : moves) {
            int n_x = x + move_x;
            int n_y = y + move_y;
            if (n_x < 0 || n_x >= n || n_y < 0 || n_y >= m) continue;

            if (dist[n_x][n_y] == -1) {
                dist[n_x][n_y] = dist[x][y] + 1;
                qu[end] = {n_x, n_y};
                ++end;
                if (g[n_x][n_y] == 1) {
                    ++cnt_q;
                    dist_sum += dist[n_x][n_y];
                    if (cnt_q == q) {
                        all_reached = true;
                        break;
                    }
                }
            }
        }
        if (all_reached) break;
    }

    if (all_reached) {
        cout << dist_sum;
    } else {
        cout << -1;
    }
}