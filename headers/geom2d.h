#ifndef GEOM_2D_HEADER
#define GEOM_2D_HEADER

#include <iostream>
#include <cmath>

using namespace std;

namespace D2 {
    const long double pi = acos(-1);
    const long double Eps = 1e-9;

    string __beg__ = "(", __sep__ = ", ", __end__ = ");";
    string __pointDescription__ = "Point";
    string __lineDescription__ = "Line";

    int sgn(const long double& a) {
        if (a > Eps) return 1;
        if (a < -Eps) return -1;
        return 0;
    }

    float toDegrees(const float& radians) {
        return radians * 180.0 / pi;
    }

    struct Point {
        long double x, y;
        bool ex;
        Point() : x(0), y(0), ex(true) {};
        Point(long double x, long double y) : x(x), y(y), ex(true) {};
        //Point(bool exist): x(0), y(0), ex(exist) {};
        Point(long double x, long double y, bool exist) : x(x), y(y), ex(exist) {};

        // Длина вектора
        long double len() const {
            if (!ex) {
                throw logic_error("Error: Point does not exist in 'long double D2::Point::len() const'");
            }
            return sqrt(x * x + y * y);
        }
        
        // Длина вектора в квадрате
        long double len2() const {
            if (!ex) {
                throw logic_error("Error: Point does not exist in 'long double D2::Point::len2() const'");
            }
            return x * x + y * y;
        }
        
        // Поворот вектора на a радиан(!) (против часовой стрелки)
        Point rotate_rad(const long double& a) const {
            if (!ex) {
                throw logic_error("Error: Point does not exist in 'D2::Point D2::Point::rotate_rad(const long double&) const'");
            }
            return Point(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a));
        }
        
        // Поворот вектора на a градусов(!) (против часовой стрелки)
        Point rotate(const long double& a) const {
            if (!ex) {
                throw logic_error("Error: Point does not exist in 'D2::Point D2::Point::rotate(const long double&) const'");
            }
            return this->rotate_rad(a * pi / 180);
        }
        
        // Угол поворота до вектора (в радианах против часовой стрелки) (-pi; pi]
        float getAngle(const Point& p) const;
        
        // Единичный вектор
        Point e() const {
            if (!ex) {
                throw logic_error("Error: Point does not exist in 'D2::Point D2::Point::e() const'");
            }
            long double len = this->len();
            if (abs(len) < Eps) return Point(0, 0);
            Point w(x / len, y / len);
            return w;
        }
        
        // Вектор, перпендикулярный данному
        Point n() const {
            if (!ex) {
                throw logic_error("Error: Point does not exist in 'D2::Point D2::Point::n() const'");
            }
            return Point(y, -x);
        }

        bool isZero() const {
            if (!ex) {
                throw logic_error("Error: Point does not exist in 'bool D2::Point::isZero() const'");
            }
            return abs(x) < Eps && abs(y) < Eps;
        }

        bool exist() const {
            return ex;
        }
    }; // Struct Point

    const Point __not_exist_point__(0, 0, false);

    Point operator + (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point operator+ (const D2::Point&, const D2::Point&)'");
        }
        return Point(p1.x + p2.x, p1.y + p2.y);
    }

    Point& operator += (Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point& operator+= (D2::Point&, const D2::Point&)'");
        }

        p1.x += p2.x;
        p1.y += p2.y;

        return p1;
    }

    Point operator + (const Point& p, const long double& a) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point operator+ (const D2::Point&, const long double&)'");
        }
        return Point(p.x + a, p.y + a);
    }
    
    Point operator + (const long double& a, const Point& p) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point operator+ (const long double&, const D2::Point&)'");
        }
        return Point(p.x + a, p.y + a);
    }
    
    Point& operator += (Point& p, const long double& a) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point& operator+= (D2::Point&, const long double&)'");
        }

        p.x += a;
        p.y += a;

        return p;
    }

    Point operator - (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point operator- (const D2::Point&, const D2::Point&)'");
        }
        return Point(p1.x - p2.x, p1.y - p2.y);
    }

    Point& operator -= (Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point& operator-= (D2::Point&, const D2::Point&)'");
        }

        p1.x -= p2.x;
        p1.y -= p2.y;

        return p1;
    }

    Point operator - (const Point& p, const long double& a) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point operator- (const D2::Point&, const long double&)'");
        }
        return Point(p.x - a, p.y - a);
    }
    
    Point operator - (const long double& a, const Point& p) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point operator- (const D2::Point&, const D2::Point&)'");
        }
        return Point(p.x - a, p.y - a);
    }
    
    Point& operator -= (Point& p, const long double& a) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point& operator-= (D2::Point&, const long double&)'");
        }

        p.x -= a;
        p.y -= a;

        return p;
    }

    long double operator * (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'long double operator* (const D2::Point&, const D2::Point&)'");
        }
        return p1.x * p2.x + p1.y * p2.y;
    }

    Point operator * (const Point& p, const long double& a) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point operator* (const D2::Point&, const long double&)'");
        }
        return Point(p.x * a, p.y * a);
    }

    Point operator * (const long double& a, const Point& p) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point operator* (const long double&, const D2::Point&)'");
        }
        return Point(p.x * a, p.y * a);
    }

    Point& operator *= (Point& p, const long double& a) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point& operator*= (D2::Point&, const long double&)'");
        }

        p.x *= a;
        p.y *= a;

        return p;
    }

    Point operator / (const Point& p, const long double& a) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point operator/ (const D2::Point&, const long double&)'");
        }
        if (abs(a) < Eps) {
            return __not_exist_point__;
        }
        return Point(p.x / a, p.y / a);
    }
    
    Point operator / (const long double& a, const Point& p) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point operator/ (const long double&, const D2::Point&)'");
        }
        if (abs(p.x) < Eps || abs(p.y) < Eps) {
            return __not_exist_point__;
        }
        return Point(a / p.x, a / p.y);
    }

    Point& operator /= (Point& p, const long double& a) {
        if (!p.ex) {
            throw logic_error("Error: Point does not exist in 'D2::Point& operator/= (D2::Point&, const long double&)'");
        }
        if (abs(a) < Eps) {
            p.ex = false;
            return p;
        }

        p.x /= a;
        p.y /= a;

        return p;
    }

    long double operator % (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'long double operator% (const D2::Point&, const D2::Point&)'");
        }
        return p1.x * p2.y - p1.y * p2.x;
    }

    bool operator || (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'bool operator|| (const D2::Point&, const D2::Point&)'");
        }
        return p1.isZero() || p2.isZero() || abs(p1.x * p2.y - p2.x * p1.y) < Eps;
    }
    bool operator == (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'bool operator== (const D2::Point&, const D2::Point&)'");
        }
        return abs(p1.x - p2.x) < Eps && abs(p1.y - p2.y) < Eps;
    }
    bool operator != (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'bool operator!= (const D2::Point&, const D2::Point&)'");
        }
        return !(p1 == p2);
    }
    bool operator < (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'bool operator< (const D2::Point&, const D2::Point&)'");
        }
        return p1.x - p2.x < -Eps || (abs(p1.x - p2.x) < Eps && p1.y - p2.y < -Eps);
    }
    bool operator <= (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'bool operator<= (const D2::Point&, const D2::Point&)'");
        }
        return p1 < p2 || p1 == p2;
    }
    bool operator > (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'bool operator> (const D2::Point&, const D2::Point&)'");
        }
        return !(p1 < p2) && !(p1 == p2);
    }
    bool operator >= (const Point& p1, const Point& p2) {
        if (!p1.ex || !p2.ex) {
            throw logic_error("Error: Point does not exist in 'bool operator>= (const D2::Point&, const D2::Point&)'");
        }
        return !(p1 < p2);
    }
    
    float Point::getAngle(const Point& p) const {
        if (!ex || !p.ex) {
            throw logic_error("Error: Point does not exist in 'float D2::Point::getAngle(const D2::Point&) const'");
        }
        long double len1 = this->len();
        long double len2 = p.len();

        if (abs(len1 * len2) < Eps) {
            return 0;
        }

        long double sin = (*this % p) / len1 / len2;
        int sin_sgn = sgn(sin);
        int cos_sgn = sgn((*this * p) / this->len() / p.len());

        if (cos_sgn == 0 && sin_sgn == 1) return pi/2;
        if (cos_sgn == 0 && sin_sgn == -1) return -pi/2;
        if (sin_sgn == 0 && cos_sgn == 1) return 0;
        if (sin_sgn == 0 && cos_sgn == -1) return pi;

        if (cos_sgn == 1) return asin(sin);
        if (cos_sgn == -1) return pi*sin_sgn - asin(sin);

        return 0;
    }




    ostream& operator << (ostream& cout, const Point& p) {
        if (p.exist()) {
            cout << __pointDescription__ << __beg__ << p.x << __sep__ << p.y << __end__;
        }
        else {
            throw logic_error("Error: Point does not exist while trying to print (in 'std::ostream& operator<< (std::ostream&, const D2::Point&)')");
        }
        return cout;
    }

    istream& operator >> (istream& cin, Point& p) {
        cin >> p.x >> p.y;
        p.ex = true;
        return cin;
    }

    struct Line {
        long double a, b, c;
        Line() : a(1), b(-1), c(0) {};
        Line(const long double& _a, const long double& _b, const long double& _c) : a(_a), b(_b), c(_c) {};
        Line(const Point& p1, const Point& p2) : a(p2.y - p1.y), b(p1.x - p2.x), c(-(a*p1.x + b*p1.y)) {
            if (!p1.ex || !p2.ex) {
                throw logic_error("Error: Point does not exist in 'D2::Line::Line(const D2::Point&, const D2::Point&)'");
            }
        };

        long double calc(const Point& p) const {
            if (!p.ex) {
                throw logic_error("Error: Point does not exist in 'long double D2::Line::calc(const D2::Point&) const'");
            }
            return a * p.x + b * p.y + c;
        }

        Point n() const {
            return Point(a, b);
        }

        Point guideVector() const {
            return Point(b, -a);
        }

        bool operator == (const Line& o) const {
            return abs(a * o.b - o.a * b) < Eps && abs(a * o.c - o.a * c) < Eps && abs(b * o.c - o.b * c) < Eps;
        }

        bool operator || (const Line& o) const {
            return abs(a * o.b - o.a * b) < Eps;
        }

        bool isZero() const {
            return abs(a) < Eps && abs(b) < Eps;
        }
    }; // Struct Line

    const Line Ox(0, 1, 0);
    const Line Oy(1, 0, 0);

    ostream& operator << (ostream& cout, const Line& l) {
        cout << __lineDescription__ << __beg__ << l.a << __sep__ << l.b << __sep__ << l.c << __end__;
        return cout;
    }

    istream& operator >> (istream& cin, Line& l) {
        cin >> l.a >> l.b >> l.c;
        return cin;
    }

    bool isCrossingLines(const Line& L1, const Line& L2) {
        return !(L1 || L2) && !(L1 == L2);
    }

    // Точка пересечения прямых
    Point crossLines(const Line& L1, const Line& L2) {
        Point w;
        long double d = L1.a * L2.b - L1.b * L2.a; // Точек пересечения 0 или бесконечность при d ~ 0

        if (abs(d) < Eps) {
            return __not_exist_point__;
        }

        w.x = (L2.c * L1.b - L1.c * L2.b) / d;
        w.y = (L1.c * L2.a - L1.a * L2.c) / d;
        return w;
    }

    Point fromPointToLine(const Point& p, const Line& l) {
        if (l.isZero()) {
            return __not_exist_point__;
        }

        long double len = abs(l.calc(p)) / sqrt(l.a*l.a + l.b*l.b);
        Point w = l.n().e() * len;
        if (abs(l.calc(p + w)) > Eps) {
            return Point(0, 0) - w;
        }
        return w;
    }

    struct Circle {
        Point center;
        long double radius;
        Circle() : center(0, 0), radius(1) {};
        Circle(const Point& p, const long double& r) : center(p), radius(r) {
            if (!p.ex) {
                throw logic_error("Error: Point does not exist in 'D2::Circle::Circle(const D2::Point&, const long double&)'");
            }
        };
        Circle(const long double& x, const long double& y, const long double& r) : center(Point(x, y)), radius(r) {};

        bool operator < (const Circle& other) const {
            return center < other.center || center == other.center && radius < other.radius;
        }
    };

    bool isPointInCircle(const Point& p, const Circle& c) {
        return (p - c.center).len() - c.radius < Eps;
    }

    bool isCrossingCircleAndLine(const Circle& C, const Line& L) {
        return fromPointToLine(C.center, L).len() - C.radius < Eps;
    }

    // Точки пересечения окружности с прямой
    pair<Point,Point> crossCircleAndLine(const Circle& C, const Line& L) {
        if (!isCrossingCircleAndLine(C, L)) {
            return make_pair(__not_exist_point__, __not_exist_point__);
        }

        Point h = fromPointToLine(C.center, L);
        long double x = sqrt(C.radius*C.radius - h.len()*h.len());
        Point x1 = L.guideVector().e() * x;
        Point x2 = L.guideVector().e() * -x;
        return make_pair(C.center+h+x1, C.center+h+x2);
    }

    bool isCrossingCircles(const Circle& C1, const Circle& C2) {
        long double l = (C1.center - C2.center).len();
        return (C2.radius - l - C1.radius < Eps) && (C1.radius - l - C2.radius < Eps) && (C1.radius + C2.radius - l > Eps);
    }

    pair<Point,Point> crossCircles(const Circle& c1, const Circle& c2) {
        if (!isCrossingCircles(c1, c2)) {
            return make_pair(__not_exist_point__, __not_exist_point__);
        }

        Point d = c1.center - c2.center;
        // a - угол между вектором d и вектором, идущим из центра с2 в точку пересечения
        long double cos_a = (d.len()*d.len() + c2.radius*c2.radius - c1.radius*c1.radius) / (2 * d.len() * c2.radius);
        Point d1 = d.e() * c2.radius * cos_a;
        long double x = sqrt(c2.radius*c2.radius - d1.len()*d1.len());
        return make_pair(c2.center + d1 + d.n().e()*x, c2.center + d1 - d.n().e()*x);
    }

    // Лежать ли точки по одну сторону от прямой (включая прямую)
    bool isInSameSide(const Line& l, const Point& a, const Point& b) {
        return l.calc(a) * l.calc(b) > -Eps;
    }

    // Лежат ли точки по одну сторону от прямой (не включая прямую)
    bool isInSameSideExcluding(const Line& l, const Point& a, const Point& b) {
        return l.calc(a) * l.calc(b) > Eps;
    }

    struct Segment {
        Point p1, p2;
        Segment(): p1(0, 0), p2(1, 1) {}
        Segment(const Point& p1, const Point& p2): p1(p1), p2(p2) {
            if (!p1.ex || !p2.ex) {
                throw logic_error("Error: Point does not exist in 'D2::Segment::Segment(const D2::Point&, const D2::Point&)'");
            }
        }
        Segment(const long double& x1, const long double& y1, const long double& x2, const long double& y2): p1(x1, y1), p2(x2, y2) {}

        long double len() const {
            return (p1 - p2).len();
        }

        bool isZero() const {
            return p1 == p2;
        }

        Line getLine() const {
            return Line(p1, p2);
        }

        Point getVector() const {
            return p2 - p1;
        }
    }; // struct Segment

    bool isPointInSegment(const Segment& s, const Point& p) {
        Point vec = s.getVector();
        Point top = p - s.p1;

        if (top.isZero() || top == vec) {
            return true;
        }

        if (!(vec || top)) {
            return false;
        }

        if (vec.e() != top.e()) {
            return false;
        }

        return top.len2() - vec.len2() < Eps;
    }

    bool isCrossingSegments(const Segment& s1, const Segment& s2) {
        Line l1 = s1.getLine();
        if (l1.isZero()) {
            return isPointInSegment(s2, s1.p1);
        }

        Line l2 = s2.getLine();
        if (l2.isZero()) {
            return isPointInSegment(s1, s2.p1);
        }

        return !isCrossingLines(l1, l2) || isPointInSegment(s1, crossLines(l1, l2));
    }

    Point crossSegments(const Segment& s1, const Segment& s2) {
        Line l1 = s1.getLine();
        if (l1.isZero()) {
            return isPointInSegment(s2, s1.p1) ? s1.p1 : __not_exist_point__;
        }

        Line l2 = s2.getLine();
        if (l2.isZero()) {
            return isPointInSegment(s1, s2.p1) ? s2.p1 : __not_exist_point__;
        }

        if (!isCrossingSegments(s1, s2)) {
            return __not_exist_point__;
        }

        return crossLines(s1.getLine(), s2.getLine());
    }
}


#endif
