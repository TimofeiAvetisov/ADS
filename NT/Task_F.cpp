#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    cout << __gcd(abs(x1 - x2), abs(y1 - y2)) + 1;
}