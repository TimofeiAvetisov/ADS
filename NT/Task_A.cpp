#include <bits/stdc++.h>

using namespace std;

int fast(int x, int n, int p) {
    int ans = 1;
    while (n > 0) {
        if (n & 1) {
            ans = ((long long)ans *  x) % p;
        }

        x = ((long long)x * x) % p;
        n >>= 1;
    }

    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int x, n, p;
    cin >> x >> n >> p;
    cout << fast(x, n, p);
}