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

inline long long cross(long long x1, long long y1, long long x2, long long y2) {
    return x1 * y2 - x2 * y1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, x_s, y_s, prev_x, prev_y,  cur_x, cur_y, ans = 0;
    cin >> n >> x_s >> y_s;
    cur_x = x_s;
    cur_y = y_s;
    for (int i = 0; i < n - 1; i++) {
        prev_x = cur_x;
        prev_y = cur_y;
        cin >> cur_x >> cur_y;
        ans += cross(cur_x, cur_y, prev_x, prev_y);
    }
    ans -= cross(cur_x, cur_y, x_s, y_s);
    cout << fixed << setprecision(5) << abs((double)ans * 0.5) << endl;

}