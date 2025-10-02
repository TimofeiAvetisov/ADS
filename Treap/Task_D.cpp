#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> edges;

bool is_valid(int bitmask) {
    for (auto [u, v] : edges) {
        if (((bitmask >> u) & 1) & ((bitmask >> v) & 1)) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;
        edges.emplace_back(u, v);
    }

    int answer = 0;
    int bit_mask = 0;
    int limit = (1 << n) - 1;
    while (bit_mask <= limit) {
        answer += is_valid(bit_mask);
        ++bit_mask;
    }
    cout << answer;
}
