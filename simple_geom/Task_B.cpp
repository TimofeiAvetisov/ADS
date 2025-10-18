#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct point{
    long long x, y;
};

struct Vector{
    long long x, y;
    Vector(point a, point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    Vector(long long x, long long y): x(x), y(y){}
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

long long dot_product(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

long long cross_product(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    point c, a, b;
    cin >> c >> a >> b;
    Vector ab(a, b), ac(a, c);
    if (cross_product(ac, ab) == 0 && dot_product(ac, ab) >= 0) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
