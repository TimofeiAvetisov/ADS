#include <bits/stdc++.h>
using namespace std;

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


struct Line {
    long long a, b, c;
    bool operator()(const Point& p) const {
        return a * p.x + b * p.y + c > 0;
    }
};

istream& operator>>(istream& in, Line &l) {
    in >> l.a >> l.b >> l.c;
    return in;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long r;
    cin >> n >> m >> r;

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i];
    }

    vector<Line> lines(m);
    for (int i = 0; i < m; ++i) {
        cin >> lines[i];
    }

    unordered_set<string> used;
    used.reserve(n * 2);

    for (auto& p : points) {
        string c;
        c.reserve(m);
        for (auto &l : lines) {
            c += (l(p) ? '1' : '0');
        }
        if (!used.insert(c).second) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";
}
