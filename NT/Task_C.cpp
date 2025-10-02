#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    while (!(n & 1)) {
        cout << 2 << ' ';
        n >>= 1;
    }

    for (int i = 3; i * i <= n; ++i) {
        if (n % i == 0) {
            cout << i << ' ';
            n /= i;
            --i;
        }
    }
    
    if (n != 1) {
        cout << n;
    }
}