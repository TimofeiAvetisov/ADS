#include <bits/stdc++.h>
using namespace std;

static vector<int> z_function(const string &s) {
    int n = (int)s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string p, t;
    if (!getline(cin, p)) return 0;
    if (!getline(cin, t)) return 0;

    int m = (int)p.size();
    int n = (int)t.size();
    if (m == 0 || m > n) {
        cout << 0 << "\n\n";
        return 0;
    }

    // L[i]: совпадения слева
    string s1 = p + '#' + t;
    vector<int> z1 = z_function(s1);
    vector<int> L(n, 0);
    for (int i = 0; i <= n - m; ++i) {
        int idx = m + 1 + i;
        L[i] = min(z1[idx], m);
    }

    // R[i]: совпадения справа (считая с конца)
    string pr = string(p.rbegin(), p.rend());
    string tr = string(t.rbegin(), t.rend());
    string s2 = pr + '#' + tr;
    vector<int> z2 = z_function(s2);
    vector<int> R(n, 0);
    for (int i = 0; i <= n - m; ++i) {
        // старт этой подстроки в перевёрнутом тексте
        int start_in_tr = n - i - m;            // 0-based
        int idx = m + 1 + start_in_tr;
        R[i] = min(z2[idx], m);
    }

    vector<int> ans;
    ans.reserve(n - m + 1);
    for (int i = 0; i <= n - m; ++i) {
        if (L[i] + R[i] >= m - 1) ans.push_back(i + 1); // 1-based
    }

    cout << ans.size() << "\n";
    for (size_t k = 0; k < ans.size(); ++k) {
        if (k) cout << ' ';
        cout << ans[k];
    }
    cout << "\n";
    return 0;
}
