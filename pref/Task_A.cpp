#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    vector<int> pref(n);
    for (int i = 1; i < n; ++i) {
        int tmp = pref[i - 1];
        while (s[i] != s[tmp] && tmp > 0) {
            tmp = pref[tmp - 1];
        }

        if (s[i] == s[tmp]) {
            pref[i] = tmp + 1;
        }
    }

    for (auto p : pref) {
        cout << p << ' ';
    }

}