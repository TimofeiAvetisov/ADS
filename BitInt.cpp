#include <bits/stdc++.h>
using namespace std;

constexpr double EPS = 1e-9;
constexpr double PI  = 3.141592653589793238462643383279502884;

/** Утилиты численной устойчивости */
inline double clamp01(double x) { return x < 0 ? 0 : (x > 1 ? 1 : x); }
inline double clampm11(double x) { return x < -1 ? -1 : (x > 1 ? 1 : x); }
inline bool equal(double a, double b) { return fabs(a - b) <= EPS; }

/** Точка на плоскости */
struct Point {
    double x, y;
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    bool operator==(const Point &o) const { return fabs(x - o.x) <= EPS && fabs(y - o.y) <= EPS; }
    bool operator!=(const Point &o) const { return !(*this == o); }
};

/** Вектор в 2D */
struct Vector {
    double x, y;
    Vector(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y) {}
};

/** Базовые операции */
inline double dot(const Vector& a, const Vector& b)   { return a.x * b.x + a.y * b.y; }
inline double cross(const Vector& a, const Vector& b) { return a.x * b.y - a.y * b.x; }
inline double length2(const Vector& a) { return dot(a, a); }
inline double length (const Vector& a) { return sqrt(length2(a)); }

/** Расстояние между точками */
inline double dist(Point a, Point b) { return hypot(a.x - b.x, a.y - b.y); }

/** Угол между двумя векторами в [0, π]; 0 при нулевом векторе */
inline double angle(const Vector& a, const Vector& b) {
    double la2 = length2(a), lb2 = length2(b);
    if (la2 <= EPS || lb2 <= EPS) return 0.0; // вырожденный случай
    double c = dot(a, b) / sqrt(la2 * lb2);
    return acos(clampm11(c));
}

/** Ориентация трёх точек: 0 — коллинеарны, +1 — влево, -1 — вправо */
inline int orientation(Point a, Point b, Point c) {
    double val = cross(Vector(a, b), Vector(a, c));
    if (fabs(val) <= EPS) return 0;
    return (val > 0 ? +1 : -1);
}

/** Точка лежит на «прямой» AB; если A==B, то «прямая» — точка A */
inline bool onLine(Point p, Point a, Point b) {
    if (a == b) return dist(p, a) <= EPS;
    return fabs(cross(Vector(a, b), Vector(a, p))) <= EPS;
}

/** Проекция точки p на «прямую» AB; если A==B — вернуть A */
inline Point projection(Point p, Point a, Point b) {
    Vector ab(a, b);
    double denom = length2(ab);
    if (denom <= EPS) return a; // вырожденная прямая-точка
    double t = dot(Vector(a, p), ab) / denom;
    return Point(a.x + t * ab.x, a.y + t * ab.y);
}

/** Расстояние от точки до «прямой» AB; если A==B — до точки A */
inline double distToLine(Point p, Point a, Point b) {
    if (a == b) return dist(p, a);
    return fabs(cross(Vector(a, b), Vector(a, p))) / length(Vector(a, b));
}

/** Расстояние от точки до отрезка AB; устойчивый вариант через проекцию */
inline double distToSegment(Point p, Point a, Point b) {
    Vector ab(a, b);
    double denom = length2(ab);
    if (denom <= EPS) return dist(p, a); // вырожденный отрезок-точка
    double t = dot(Vector(a, p), ab) / denom;
    t = clamp01(t);
    Point q(a.x + t * ab.x, a.y + t * ab.y);
    return dist(p, q);
}

/** Точка лежит на отрезке AB; корректно обрабатывает A==B */
inline bool onSegment(Point p, Point a, Point b) {
    if (!onLine(p, a, b)) return false;
    if (a == b) return dist(p, a) <= EPS;
    double minx = min(a.x, b.x) - EPS, maxx = max(a.x, b.x) + EPS;
    double miny = min(a.y, b.y) - EPS, maxy = max(a.y, b.y) + EPS;
    return (p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy);
}

/** Точка лежит на луче AB; если A==B — только p==A */
inline bool onRay(Point p, Point a, Point b) {
    if (!onLine(p, a, b)) return false;
    if (a == b) return p == a;
    return dot(Vector(a, b), Vector(a, p)) >= -EPS;
}

/** Пересечение отрезков AB и CD (включая касания и коллинеарные наложения) */
inline bool intersectSegments(Point A, Point B, Point C, Point D) {
    int o1 = orientation(A, B, C);
    int o2 = orientation(A, B, D);
    int o3 = orientation(C, D, A);
    int o4 = orientation(C, D, B);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(C, A, B)) return true;
    if (o2 == 0 && onSegment(D, A, B)) return true;
    if (o3 == 0 && onSegment(A, C, D)) return true;
    if (o4 == 0 && onSegment(B, C, D)) return true;

    return false;
}

/** Точка пересечения прямых AB и CD; если параллельны — {NaN, NaN} */
inline Point intersection(Point A, Point B, Point C, Point D) {
    Vector a(B.x - A.x, B.y - A.y);
    Vector b(D.x - C.x, D.y - C.y);
    Vector c(C.x - A.x, C.y - A.y);
    double denom = cross(a, b);
    if (fabs(denom) <= EPS) return Point(numeric_limits<double>::quiet_NaN(),
                                         numeric_limits<double>::quiet_NaN());
    double t = cross(c, b) / denom;
    return Point(A.x + t * a.x, A.y + t * a.y);
}

/** Площадь треугольника ABC (>=0) */
inline double areaTriangle(Point a, Point b, Point c) {
    return fabs(cross(Vector(a, b), Vector(a, c))) * 0.5;
}

/** Площадь многоугольника по списку вершин (>=0). Ожидается порядок обхода. */
inline double areaPolygon(const vector<Point>& p) {
    int n = (int)p.size();
    if (n < 3) return 0.0;
    long double s = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        s += (long double)p[i].x * p[j].y - (long double)p[j].x * p[i].y;
    }
    return (double)fabs(s) * 0.5;
}

/** Угол ABC в радианах (0..π); 0 при вырождении */
inline double angleAt(Point A, Point B, Point C) {
    Vector BA(B, A), BC(B, C);
    return angle(BA, BC);
}

/** Параллельность и перпендикулярность с относительной нормировкой */
inline bool parallel(const Vector& a, const Vector& b) {
    double la = length(a), lb = length(b);
    if (la <= EPS || lb <= EPS) return la <= EPS && lb <= EPS; // оба нулевые считаем параллельными
    return fabs(cross(a, b)) <= EPS * la * lb;
}
inline bool perpendicular(const Vector& a, const Vector& b) {
    double la = length(a), lb = length(b);
    if (la <= EPS || lb <= EPS) return false;
    return fabs(dot(a, b)) <= EPS * la * lb;
}

int main() {
    return 0;
}
