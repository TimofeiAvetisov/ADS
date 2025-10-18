#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct Point {
    long long x, y;
    bool operator<(Point& other)  {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(Point& other)  {
        return x == other.x && y == other.y;
    }
};

istream& operator>>(istream& in, Point &p) {
    in >> p.x >> p.y;
    return in;
}

long long cmp(Point& a, Point& b, Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long double d(Point& a,  Point& b) {
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

vector<Point> convex(vector<Point>& points) {
    if (points.size() <= 1) {
        return points;
    }
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    if (points.size() == 1) {
        return points;
    }

    vector<Point> ans, helper;
    for (auto& p : points) {
        while (ans.size() >= 2 && cmp(ans[ans.size() - 2], ans.back(), p) <= 0) {
            ans.pop_back();
        }
        ans.push_back(p);
    }
    for (int i = points.size() - 1; i >= 0; --i) {
        auto& p = points[i];
        while (helper.size() >= 2 && cmp(helper[helper.size()-2], helper.back(), p) <= 0) {
            helper.pop_back();
        }
        helper.push_back(p);
    }
    ans.pop_back();
    helper.pop_back();
    ans.insert(ans.end(), helper.begin(), helper.end());
    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i];
    }

    vector<Point> ans = convex(points);
    long double p = 0.0;
    for (int i = 0; i < ans.size(); ++i) {
        p += d(ans[i], ans[(i + 1) % ans.size()]);
    }
    ll s = 0;
    for (size_t i = 0; i < ans.size(); ++i) {
        s += ans[i].x * ans[(i + 1) % ans.size()].y - ans[i].y * ans[(i + 1) % ans.size()].x;
    }

    cout << fixed;
    cout.precision(10);
    cout << p << '\n' << (long double)s * 0.5 << '\n';
}
