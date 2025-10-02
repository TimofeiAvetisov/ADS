#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<bool> is_prime(m + 1, true);

    for (int p = 2; p * p <= m; ++p) {
        if (is_prime[p]) {
            for (int i = 2 * p; i <= m; i += p) {
                is_prime[i] = false;
            }
        }
    }

    bool out = false;
    for (int i = max(n, 2); i <= m; ++i) {
        if (is_prime[i]) {
            out = true;
            cout << i << '\n';
        }
    }

    if (!out) {
        cout << "Absent";
    }
}