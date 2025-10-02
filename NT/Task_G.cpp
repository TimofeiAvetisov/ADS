#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a;
    cin >> a;
    map<int, int> p;

    while (!(n & 1)) {
        p[2] += 1;
        n >>= 1;
    }

    for (int i = 3; i * i <= n; ++i) {
        if (n % i == 0) {
            p[i] += 1;
            n /= i;
            --i;
        }
    }

    map<int, int> np;

    
    for (auto [key, val] : p) {

    }
}