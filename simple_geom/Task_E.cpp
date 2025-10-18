#include <iostream>

using namespace std;
const double pres = 1e-9;
struct point {
    long long x, y;
    point(long long a, long long b) {
        x = a;
        y = b;
    }
    point() {
        x = 0;
        y = 0;
    }
};

struct line {
    double a, b, c;
    line(point q, point p) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = - (a * p.x + b * p.y);
    }
    line(long long a_, long long b_, long long c_) {
        a = a_;
        b = b_;
        c = c_;
    }
    line() {
        a = 0;
        b = 0;
        c = 0;
    }
};

istream& operator>>(istream& in, point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, line& l) {
    out << l.a << ' ' << l.b << ' ' << l.c;
    return out;
}

int main() {
    point a, b, c, d;
    cin >> a >> b >> c >> d;

    line l1(a, b);
    line l2(c, d);

    double det = l1.a * l2.b - l2.a * l1.b;

    if (abs(det) < pres) {
        if (abs(l1.a * l2.c - l2.a * l1.c) < pres &&
            abs(l1.b * l2.c - l2.b * l1.c) < pres) {
            cout << 2 << '\n';
        } else {
            cout << 0 << '\n';
        }
    } else {
        double x = (l1.b * l2.c - l2.b * l1.c) / det;
        double y = (l2.a * l1.c - l1.a * l2.c) / det;
        if(x == 0) {
            x = 0;
        }
        if (y == 0) {
            y = 0;
        }
        cout << 1 << ' ';
        cout << fixed;
        cout.precision(2);
        cout << x << ' ' << y << '\n';
    }
}
