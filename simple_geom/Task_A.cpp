#include <iostream>

using namespace std;

struct point{
    long long x, y;
    point(long long a, long long b) {
        x = a;
        y =  b;
    }
    point(){
        x = 0;
        y = 0;
    }
};

struct line{
    double a, b, c;
    line(point q, point p){
        a = p.y - q.y;
        b = q.x - p.x;
        c = - (a * p.x + b * p.y);
    }
    line(long long a, long long b, long long c){
        a = a;
        b = b;
        c = c;
    }
    line(){
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
    point a, b;
    cin >> a >> b;
    line l(a, b);
    cout << l;
}