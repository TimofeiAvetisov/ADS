#include <bits/stdc++.h>

using namespace std;
#define ld long double

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ld x, y;
    cin >> x >> y;

    ld x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    ld a1 = 1 - (x2 - x1) / x;
    ld b1 = -(x3 - x2) / y;

    ld a2 = -(y2 - y1) / x;
    ld b2 = 1 - (y3 - y2) / y;

    ld d = a1 * b2 - a2 * b1;

    cout << fixed << setprecision(3) << (x1 * b2 - y1 * b1) / d << " " << (a1 * y1 - a2 * x1) / d << '\n';
}
