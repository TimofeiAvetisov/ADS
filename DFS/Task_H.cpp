#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<vector<bool>> vis;
int answer = 0;
vector<pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void dfs(int x, int y) {
    if (vis[x][y]) return;

    vis[x][y] = true;
    ++answer;
    for (auto move : moves) {
        int tmp_x, tmp_y;
        tmp_x = x + move.first;
        tmp_y = y + move.second;
        if (g[tmp_x][tmp_y]) {
            dfs(tmp_x, tmp_y);
        }
    }
}

int main() {
    int n;
    cin >> n;
    g.resize(n, vector<int>(n, 1));
    vis.resize(n, vector<bool>(n, false));
    for (int i = 0; i< n; ++i) {
        for (int j = 0; j < n; ++j) {
            char tmp;
            cin >> tmp;
            if (tmp == '*') {
                g[i][j] = 0;
            }
        }
    }

    int x, y;
    cin >> x >> y;
    --y;--x;

    dfs(x, y);

    cout << answer;

}