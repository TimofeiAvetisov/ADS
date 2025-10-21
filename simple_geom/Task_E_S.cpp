#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <chrono>
#include <cstdlib>
#include <limits>
#include <unordered_map>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    double a1 = y2 - y1;
    double b1 = x1 - x2;
    double c1 = - (a1 * x2 + b1 * y2);
    double a2 = y4 - y3;
    double b2 = x3 - x4;
    double c2 = - (a2 * x4 + b2 * y4);
    double d = a1 * b2 - a2 * b1;
    if (abs(d) < 0.00000000001) {
        if (abs(a1 * c2 - a2 * c1)  < 0.00000000001 && abs(b1 * c2 - b2 * c1) < 0.00000000001) {
            cout << 2 << endl;
        } else {
            cout << 0 << endl;
        }
        return 0;
    }

    double x = (b1 * c2 - b2 * c1) / d;
    double y = (a2 * c1 - a1 * c2) / d;
    if (x == 0) {
        x = 0;
    }
    if (y == 0) {
        y = 0;
    }

    cout << fixed << setprecision(5) << 1 << ' ' << x << ' ' << y << endl;

}