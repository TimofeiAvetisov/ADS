#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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
    Vector(point a): x(a.x), y(a.y) {}
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

inline ll dot_product(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

inline ll cross_product(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    int n;
    cin >> n;
    vector<Vector> points(n);
    ll offest = 2e4;
    for (int i = 0; i < n; ++i) {
        point tmp;
        cin >> tmp;
        tmp.x += offest;
        tmp.y += offest;
        points[i] = Vector(tmp);
    }
    ll S = 0;
    for (int i = 0; i < n - 1; ++i) {
        S += cross_product(points[i], points[i + 1]);
    }
    S += cross_product(points[n - 1], points[0]);
    long double ans = (long double)S;
    ans *= (double)0.5;
    cout << fixed;
    cout.precision(5);
    cout << abs(ans)<< '\n';
}
