#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<bool> is_prime(n + 1, true);

    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = 2 * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 2; i < n - 1; ++i) {
        if (is_prime[i] && is_prime[n - i]) {
            cout << i << ' ' << n - i << '\n';
            return 0;
        }
    }
}

