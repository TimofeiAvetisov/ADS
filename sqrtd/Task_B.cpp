#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;


    int sqrt = 1;
    for (sqrt; sqrt * sqrt < n; ++sqrt);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<pair<int, int>> d(n);
    for (int j = sqrt; j >= 0; --j) {
        for (int i = sqrt - 1; i >= 0; --i) {
            int pos = j * sqrt + i;
            if (pos >= n) {
                continue;
            }

            if (pos + a[pos] >= min(n, sqrt * (j + 1))) {
                d[pos] = {pos, 1};
            } else {
                d[pos] = {d[pos + a[pos]].first, d[pos + a[pos]].second + 1};
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos;
            cin >> pos;
            --pos;

            int ans = 0;
            while (d[pos].first + a[d[pos].first] < n) {
                ans += d[pos].second;
                pos = d[pos].first + a[d[pos].first];
            }

            cout << d[pos].first + 1 << ' ' << ans + d[pos].second << '\n';
        } else {
            int init_pos, val;
            cin >> init_pos >> val;
            --init_pos;
            a[init_pos] = val;
            int block = init_pos / sqrt;
            for (int i = sqrt - 1; i >= 0; --i) {
                int pos = sqrt * block + i;
                if (pos >= n) {
                    continue;
                }

                if (pos + a[pos] >= min(n, sqrt * (block + 1))) {
                    d[pos] = {pos, 1};
                } else {
                    d[pos] = {d[pos + a[pos]].first, d[pos + a[pos]].second + 1};
                }
                
            }
        }
    }


}