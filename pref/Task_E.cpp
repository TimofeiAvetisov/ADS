#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>

using namespace std;

#define int long long

const string alphabet = "abcdefghijklmnopqrstuvwxyz";

vector<int> pref_function(string &s) {
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

    return pref;
}

vector<vector<int>> build_kmp(string &p, int a) {
    int m = p.size();
    vector<int> pref = pref_function(p);
    vector<vector<int>> kmp(m + 1, vector<int>(a));
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j < a; ++j) {
            if (i > 0 && alphabet[j] != p[i]) {
                kmp[i][j] = kmp[pref[i - 1]][j];
            } else if (alphabet[j] == p[i]) {
                kmp[i][j] = i + 1;
            } else {
                kmp[i][j] = i;
            }
        }
    }

    return kmp;
}

int find_best(vector<vector<int>>& kmp, int m, int n, int a, int k) {
    return ranges::max(
        views::iota(0, m) | views::transform([&](int i) {
            return ranges::max(
                views::iota(0, a) | views::transform([&](int c) {
                    return max((long long)0, i - kmp[i][c]);
                })
            );
        })
    );
}


int find_best(vector<vector<int>>& kmp, int m, int n, int a, int k) {
    int answer = 0;
    for (int i = 0; i < m; ++i) {
        for (int c = 0; c < a; ++c) {
            int ans = i - kmp[i][c];
            //cout << i << ' ' << ' ' << c << ' ' << ans << '\n';
            max(answer, ans);
        }
    }

    return answer;
}

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, a, k;
    cin >> n >> a >> k;
    string p;
    cin >> p;
    vector<vector<int>> kmp = build_kmp(p, a);
    int m = p.size();
    int ans = find_best(kmp, m, n, a, k);
    cout << m + ans * k << '\n';
}
