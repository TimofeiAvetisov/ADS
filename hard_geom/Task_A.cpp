#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;
#define ll long long


struct point{
    ll x, y;
    point(ll x_, ll y_) : x(x_), y(y_) {}
    point() : x(0), y(0) {}
};

bool operator==(const point a, const point b) {
    return a.x == b.x && a.y == b.y;
}

struct Vector{
    ll x, y;
    Vector(point a, point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    Vector(ll x, ll y): x(x), y(y){}
    Vector(){
        x = 0;
        y = 0;
    }
};

istream& operator>>(istream& in, point &p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, Vector a) {
    out << a.x << ' ' << a.y;
    return out;
}

ll dot_product(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

ll cross_product(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool intersect(ll a, ll b, ll c, ll d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

bool segments_intersect(point a, point b, point c, point d) {
    Vector ab(a, b), ac(a, c), ad(a, d);
    Vector cd(c, d), ca(c, a), cb(c, b);

    ll c1 = cross_product(ab, ac);
    ll c2 = cross_product(ab, ad);
    ll c3 = cross_product(cd, ca);
    ll c4 = cross_product(cd, cb);

    if (!intersect(a.x, b.x, c.x, d.x) || !intersect(a.y, b.y, c.y, d.y))
        return false;

    return c1 * c2 <= 0 && c3 * c4 <= 0;
}

int main() {
    int n;
    cin >> n;
    vector<point> points;
    point a;
    cin >> a;
    points.reserve(n);
    for (int i = 0; i < n; ++i) {
        point tmp;
        cin >> tmp;
        points.push_back(tmp);
    }
    const double PI = acos(-1);
    double angle = 1.0 * PI / 180.0;
    long long len = 1000000; 

    point special(
        a.x + (ll)round(cos(angle) * len),
        a.y + (ll)round(sin(angle) * len)
    );
    Vector ray(a, special);
    int s = 0;
    // point c, a, b;
    // cin >> c >> a >> b;
    // Vector ab(a, b), ac(a, c), bc(b, c), ba(b, a);
    // if (cross_product(ac, ab) == 0 && dot_product(ac, ab) >= 0 && dot_product(bc, ba) >= 0) {
    //     cout << "YES";
    // } else {
    //     cout << "NO";
    // }
    for (int i = 0; i < n; ++i) {
        Vector ab(points[i],  points[(i + 1) % n]), ac(points[i], a), bc(points[(i + 1) % n], a), ba(points[(i + 1) % n], points[i]);
        if (a == points[i] || (cross_product(ac, ab) == 0 && dot_product(ac, ab) >= 0 && dot_product(bc, ba) >= 0)) {
            cout << "YES\n";
            return 0;
        }
        s += segments_intersect(points[i], points[(i + 1) % n], a, special);
    }
    if (s % 2) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
