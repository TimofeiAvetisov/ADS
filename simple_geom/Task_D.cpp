#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;
#define ll long long
struct point{
    ll x, y;
};

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
    point a, b, c, d;
    cin >> a >> b >> c >> d;
    if (segments_intersect(a, b, c, d)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

}
