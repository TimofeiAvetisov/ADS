#include <bits/stdc++.h>

using namespace std;

void z_function(const string &s, vector<int> &z) {
    int n = s.size();
    int l = 0, r = 0;
    for(int i = 1; i < n; ++i) {            
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }

        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string p, t;
    cin >> p >> t;
    int n = p.size();
    int m = t.size();
    if (n == 0 || n > m) {
        cout << 0 << "\n\n";
        return 0;
    }

    string s = p + "#" + t;
    vector<int> zl(s.size());
    z_function(s, zl);
    vector<int> Lres(m);
    for (int i = 0; i <= m - n; ++i) {
        Lres[i] = min(zl[i + n + 1], n);
    }
    reverse(p.begin(), p.end()); reverse(t.begin(), t.end());
    s = p + "#" + t;
    vector<int> zr(s.size());
    z_function(s, zr);
    vector<int> Rres(m);
    for (int i = 0; i <= m - n; ++i) {
        Rres[i] = min(zr[m - i + 1], n); // ну пожалуйста
    }

    vector<int> ans;
    ans.reserve(m - n + 1);
    for (int i = 0; i <= m - n; ++i) {
        if (Lres[i] + Rres[i] >= n - 1) {
            ans.push_back(i + 1);
        }
    }

    cout << ans.size() << '\n';
    for (auto q : ans) {
        cout << q << ' ';
    }

}