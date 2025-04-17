#include <bits/stdc++.h>

using namespace std;


struct apple {
    apple(int x_1, int y_1, int z_1, int r_1) : x(x_1), y(y_1), z(z_1), r(r_1) {};
    apple() = default;
    int x, y, z;
    int r;
};

vector<apple> apples; 
vector<vector<int>> g;
vector<bool> vis;
vector<int> answer;

bool collision(apple& a, apple& b) {
    if (a.z <= b.z) {
        return false;
    }

    int dx = a.x - b.x;
    int dy = a.y - b.y;
    int dist = a.r + b.r;

    return (dx * dx + dy * dy <= dist * dist);
}

void dfs(int u) {
    if (vis[u]) return;

    vis[u] = true;
    for (auto v : g[u]) {
        dfs(v);
    }

    answer.push_back(u);
}

int main() {
    int n;
    cin >> n;
    apples.resize(n);
    g.resize(n);
    vis.resize(n);
    for (int i = 0; i < n; ++i) {
        int x, y, z, r;
        cin >> x >> y >> z >> r;
        apple tmp(x, y, z - r, r);
        apples[i] = tmp;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (collision(apples[i], apples[j])) {
                g[i].push_back(j);
            }
        }
    }

    dfs(0);

    
    cout << answer.size() << '\n';
    for (int i = answer.size() - 1; i >= 0; --i) {
        cout << answer[i] + 1 << ' ';
    }
}