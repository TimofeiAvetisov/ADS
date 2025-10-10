#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long n;
    cin >> n;

    vector<long long> m(n + 1, 0);
    vector<long long> pr(n + 1, 0);
    long long answer = 0;

    for (long long i = 1; i <= n; ++i) {
        long long ind, mass;
        cin >> ind >> mass;
        if (mass == 0) {
            pr[i] = pr[pr[ind]];
            m[i] = m[pr[ind]];
        } else {
            pr[i] = ind;
            m[i] = m[ind] + mass;
        }
        answer += m[i];
    }

    cout << answer;
}