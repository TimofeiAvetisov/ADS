#include <bits/stdc++.h>

using namespace std;


int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 2, vector<int>(m + 2, 1));

    for (int i = 0; i < n + 2; ++i) {
        for (int j = 0; j < m + 2; ++j) {
            if (i == 0 || j == 0 || i == n + 1 || j == m + 1) {
                g[i][j] = 0;
                continue;
            }
            char tmp;
            cin >> tmp;
            if (tmp == 'X') {
                g[i][j] = 0;
            }
        }
    }

    int s_x, s_y, f_x, f_y;
    cin >> s_y >> s_x >> f_y >> f_x;
    s_x = n + 1 - s_x;
    f_x = n + 1 - f_x;
    vector<vector<vector<int>>> dist(n + 2, vector<vector<int> >(m + 2, vector<int>(8, -1)));
    queue<pair<pair<int, int>, int>> q;
    vector<pair<int, int>> dirs = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
    };
    int start = 0, end = 8;
    for (int i = 0; i < 8; ++i) {
        q.push({{s_x, s_y}, i});
        dist[s_x][s_y][i] = 1;
    }
    while(!q.empty()) {
        auto [cord, dir] = q.front(); q.pop();
        int cord_x = cord.first, cord_y = cord.second;

        for (int i = 0; i < 8; ++i) {
            auto [x, y] = dirs[i];
            int delta = (dir == i ? 0 : 1);
            int n_cord_x = cord_x + x;
            int n_cord_y = cord_y + y;
            while(g[n_cord_x][n_cord_y] == 1) {
                if (dist[n_cord_x][n_cord_y][i] == -1 || dist[n_cord_x][n_cord_y][i] > dist[cord_x][cord_y][dir] + delta) {
                    dist[n_cord_x][n_cord_y][i] = dist[cord_x][cord_y][dir] + delta;
                    q.push({{n_cord_x, n_cord_y}, i});
                } else {
                    break;
                }
                n_cord_x += x;
                n_cord_y += y;
            }
        }
    }
    int answer = -1;
    for (int i = 0; i < 8; ++i) {
        if (answer == -1 || dist[f_x][f_y][i] < answer) {
            if (dist[f_x][f_y][i] != -1) {
                answer = dist[f_x][f_y][i];
            }
        }
    }

    cout << answer << '\n';


}