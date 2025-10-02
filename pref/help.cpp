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
    vector<int> pr = pref_function(p);
    vector<vector<int>> kmp(m + 1, vector<int>(a));
    
    for (int i = 0; i < m + 1; i++) {
        for (int j = 0; j < a; j++) {
            if (i == 0 and alphabet[j] != p[i]) {
                kmp[i][j] = 0;
                continue;
            }
            if (alphabet[j] == p[i]) {
                kmp[i][j] = i + 1;
                continue;
            }

            kmp[i][j] = kmp[pr[i - 1]][j];
        }
    }

    return kmp;
}

int find_best(vector<vector<int>>& kmp, int m, int n, int a, int k) {
    int maxx = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < a; j++){
            cout << i << " " << i - kmp[i][j] << endl;
            maxx = max(maxx, i-kmp[i][j]);

        }
    }

    return maxx;
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
