#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
    }

    vector<bool> used(n, false);
    int ans = 1;

    for (int i = 0; i < n; ++i) {
        int ind = i;
        int tmp = 0;
        while (!used[ind]) {
            ++tmp;
            used[ind] = true;
            ind = p[ind];
        }
        if (tmp == 0) {
            continue;
        }
        ans = lcm(ans, tmp);
    }

    cout << ans;
}