#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

/**
 * @brief Точка на плоскости
 */
struct Point {
    double x, y;
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    bool operator==(const Point &o) const { return fabs(x - o.x) < EPS && fabs(y - o.y) < EPS; }
    bool operator!=(const Point &o) const { return !(*this == o); }
};

/**
 * @brief Вектор в 2D-пространстве
 */
struct Vector {
    double x, y;
    Vector(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y) {}
};

/**
 * @brief Скалярное произведение двух векторов
 * @param a Вектор 1
 * @param b Вектор 2
 * @return Число — результат скалярного произведения
 */
inline double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }

/**
 * @brief Векторное произведение (псевдоскаляр в 2D)
 * @param a Вектор 1
 * @param b Вектор 2
 * @return Площадь параллелограмма, построенного на векторах
 */
inline double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

/**
 * @brief Длина вектора
 * @param a Вектор
 * @return Длина вектора
 */
inline double length(Vector a) { return sqrt(dot(a, a)); }

/**
 * @brief Угол между двумя векторами
 * @param a Вектор 1
 * @param b Вектор 2
 * @return Угол в радианах (0..π)
 */
inline double angle(Vector a, Vector b) { return acos(dot(a, b) / (length(a) * length(b))); }

/**
 * @brief Расстояние между двумя точками
 */
inline double dist(Point a, Point b) { return hypot(a.x - b.x, a.y - b.y); }

/**
 * @brief Проверка равенства с учётом EPS
 */
inline bool equal(double a, double b) { return fabs(a - b) < EPS; }

/**
 * @brief Расстояние от точки до прямой AB
 */
inline double distToLine(Point p, Point a, Point b) {
    return fabs(cross(Vector(a, b), Vector(a, p))) / dist(a, b);
}

/**
 * @brief Расстояние от точки до отрезка AB
 */
inline double distToSegment(Point p, Point a, Point b) {
    Vector ab(a, b), ap(a, p), bp(b, p);
    if (dot(ab, ap) < 0) return dist(a, p);
    if (dot(ab, bp) > 0) return dist(b, p);
    return fabs(cross(ab, ap)) / length(ab);
}

/**
 * @brief Проверка: точка лежит на прямой AB
 */
inline bool onLine(Point p, Point a, Point b) {
    return fabs(cross(Vector(a, b), Vector(a, p))) < EPS;
}

/**
 * @brief Проверка: точка лежит на отрезке AB
 */
inline bool onSegment(Point p, Point a, Point b) {
    return onLine(p, a, b) &&
           (p.x - a.x) * (p.x - b.x) <= EPS &&
           (p.y - a.y) * (p.y - b.y) <= EPS;
}

/**
 * @brief Проверка: точка лежит на луче AB
 */
inline bool onRay(Point p, Point a, Point b) {
    if (!onLine(p, a, b)) return false;
    return dot(Vector(a, b), Vector(a, p)) >= -EPS;
}

/**
 * @brief Проверка пересечения отрезков AB и CD
 * @return true, если пересекаются
 */
inline bool intersectSegments(Point A, Point B, Point C, Point D) {
    auto cross1 = cross(Vector(A, B), Vector(A, C));
    auto cross2 = cross(Vector(A, B), Vector(A, D));
    auto cross3 = cross(Vector(C, D), Vector(C, A));
    auto cross4 = cross(Vector(C, D), Vector(C, B));

    if ((cross1 * cross2 < -EPS) && (cross3 * cross4 < -EPS)) return true;
    if (fabs(cross1) < EPS && onSegment(C, A, B)) return true;
    if (fabs(cross2) < EPS && onSegment(D, A, B)) return true;
    if (fabs(cross3) < EPS && onSegment(A, C, D)) return true;
    if (fabs(cross4) < EPS && onSegment(B, C, D)) return true;
    return false;
}

/**
 * @brief Точка пересечения прямых AB и CD
 * @note Работает только если прямые не параллельны
 */
inline Point intersection(Point A, Point B, Point C, Point D) {
    Vector a(B.x - A.x, B.y - A.y);
    Vector b(D.x - C.x, D.y - C.y);
    Vector c(C.x - A.x, C.y - A.y);
    double t = cross(c, b) / cross(a, b);
    return Point(A.x + t * a.x, A.y + t * a.y);
}

/**
 * @brief Площадь треугольника ABC
 */
inline double areaTriangle(Point a, Point b, Point c) {
    return fabs(cross(Vector(a, b), Vector(a, c))) / 2.0;
}

/**
 * @brief Площадь многоугольника (по списку вершин)
 * @param p Вектора вершин (в порядке обхода)
 */
inline double areaPolygon(const vector<Point>& p) {
    double s = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        int j = (i + 1) % p.size();
        s += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return fabs(s) / 2.0;
}

/**
 * @brief Ориентация трёх точек
 * @return 0 — коллинеарны, +1 — поворот влево, -1 — вправо
 */
inline int orientation(Point a, Point b, Point c) {
    double val = cross(Vector(a, b), Vector(a, c));
    if (fabs(val) < EPS) return 0;
    return (val > 0 ? +1 : -1);
}

/**
 * @brief Угол ABC (в радианах)
 */
inline double angleAt(Point A, Point B, Point C) {
    Vector BA(B, A), BC(B, C);
    return acos(dot(BA, BC) / (length(BA) * length(BC)));
}

/**
 * @brief Проекция точки p на прямую AB
 */
inline Point projection(Point p, Point a, Point b) {
    Vector ab(a, b);
    double t = dot(Vector(a, p), ab) / dot(ab, ab);
    return Point(a.x + t * ab.x, a.y + t * ab.y);
}

bool parallel(Vector a, Vector b) { return fabs(cross(a, b)) < EPS; }
bool perpendicular(Vector a, Vector b) { return fabs(dot(a, b)) < EPS; }



int main() {
}