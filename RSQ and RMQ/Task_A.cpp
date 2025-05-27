#include <bits/stdc++.h>

using namespace std;

#define int long  long

const int mod = 1e9 + 7;

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 1; i < n + 1; ++i) {
        pref[i] = pref[i - 1] + a[i - 1];
    }

    int q, x;
    cin >> q >> x;
    int y = ((long long)11173 * x + 1) % mod;

    int l, r;
    l = min(x % n, y % n);
    r = max(x % n, y % n);

    int answer = 0;

    for (int i = 0; i < q; ++i) {
        answer = (answer + pref[r + 1] - pref[l]) % mod;

        x = ((long long)11173 * y + 1) % mod;
        y = ((long long)11173 * x + 1) % mod;
        l = min(x % n, y % n);
        r = max(x % n, y % n);
    }

    cout << answer;
}