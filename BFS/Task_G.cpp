#include <bits/stdc++.h>

using namespace std;

pair<int, int> find_stop(pair<int, int> pos, vector<vector<int>> &g, pair<int, int> dir) {
    while (g[pos.first + dir.first][pos.second + dir.second] != 1 &&  g[pos.first][pos.second] != 2){
        pos = {pos.first + dir.first, pos.second + dir.second};
    }

    return pos;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 2, vector<int>(m + 2, 1));
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            int tmp;
            cin >> tmp;
            g[i][j] = tmp;
        }
    }

    vector<pair<int, int>> q(4 * n * m);
    vector<vector<int>> dist(n + 2, vector<int>(m + 2, -1));
    int answer = 1e9;
    int start = 0, end = 1;
    q[0] = {1, 1};
    dist[1][1] = 0;

    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while(start != end) {
        auto pos = q[start++];
        for (auto dir : dirs) {
            auto stop_pos = find_stop(pos, g, dir);
            if (g[stop_pos.first][stop_pos.second] == 2) {
                cout << dist[pos.first][pos.second] + 1;
                return 0;
            }
            int d = dist[stop_pos.first][stop_pos.second]; 
            if (d == -1 || d > dist[pos.first][pos.second] + 1) {
                dist[stop_pos.first][stop_pos.second] = dist[pos.first][pos.second] + 1;
                q[end++] = stop_pos;
            }
        }
    }
}