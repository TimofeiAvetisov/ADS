#include <bits/stdc++.h>
#include <tuple>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<vector<bool>>> g(n, vector<vector<bool>>(n, vector<bool>(n, false)));
    int s_x, s_y, s_z;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; k++) {
                char tmp;
                cin >> tmp;
                if (tmp == 'S') {
                    tie(s_x, s_y, s_z) = make_tuple(i, j, k);
                }
                g[i][j][k] = (tmp == '#' ? false : true);
            }
        }
    }
    vector<tuple<int, int, int>> q(2 * n * n * n);
    vector<vector<int>> moves = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(n, vector<int>(n, -1)));
    dist[s_x][s_y][s_z] = 0;
    int start = 0, end = 1;
    q[0] = make_tuple(s_x, s_y, s_z);

    while(start != end) {
        auto [v_x, v_y, v_z] = q[start];
        ++start;
    
        for (auto move : moves) {
            int u_x = 0, u_y = 0, u_z = 0;
            tie(u_x, u_y, u_z) = make_tuple(v_x + move[0], v_y + move[1], v_z + move[2]);
            if (u_x < 0 || u_x >= n || u_y < 0 || u_y >= n || u_z < 0 || u_z >= n) {
                continue;
            }
            if (g[u_x][u_y][u_z] && dist[u_x][u_y][u_z] == -1) {
                q[end] = {u_x, u_y, u_z};
                ++end;
                dist[u_x][u_y][u_z] = dist[v_x][v_y][v_z] + 1;
                if (u_x == 0) {
                    cout << dist[u_x][u_y][u_z];

                    return 0;
                }
            }
        }
    }
}