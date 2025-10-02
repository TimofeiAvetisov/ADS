#include <bits/stdc++.h>

using namespace std;

#define int long long

int lcm(int a, int b) {
    return (a * b / __gcd(a, b));
}

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int ans = a[0] + 1;
    for (int i = 1; i < n; ++i) {
        ans = lcm(ans, a[i] + 1);
    }

    cout << ans - 1;
}