#include <bits/stdc++.h>

using namespace std;

#define int long long

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

    int mip = 0;
    int answer = -INT_MAX;
    vector<int> pref(n + 1);
    pref[0] = 0;
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];
        answer = max(answer, pref[i + 1] - mip);
        mip = min(pref[i + 1], mip);
    }

    cout << answer;
}