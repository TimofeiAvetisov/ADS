#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    int a = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            a = max(i, max(n / i, a));
        }
    }

    cout << a << ' ' << n - a;
}