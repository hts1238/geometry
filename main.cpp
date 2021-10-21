#include <bits/stdc++.h>

using namespace std;

const long double pi = acos(-1);
const long double Eps = 1e-9;

struct point {
    long double x, y;
    point() : x(0), y(0) {};
    point(long double _x, long double _y) : x(_x), y(_y) {};

    // Сложение векторов
    point operator + (const point& other) const {
        return point(x + other.x, y + other.y);
    }
    // Вычитание векторов
    point operator - (const point& other) const {
        return point(x - other.x, y - other.y);
    }
    // Скалярное произведение векторов
    long double operator * (const point& other) const {
        return x * other.x + y * other.y;
    }
    // Растягивание вектора
    point operator * (const long double& a) const {
        return point(x * a, y * a);
    }
    // Сжатие вектора
    point operator / (const long double& a) const {
        return point(x / a, y / a);
    }
    // Векторное произведение векторов
    long double operator % (const point& other) const {
        return x * other.y - y * other.x;
    }
    // Проверка на параллельность векторов
    bool operator || (const point& other) const {
        return abs(x * other.y - other.x * y) < Eps;
    }
    bool operator == (const point& other) const {
        return abs(x - other.x) < Eps && abs(y - other.y) < Eps;
    }
    bool operator != (const point& other) const {
        return !(*this == other);
    }
    bool operator < (const point& other) const {
        return x - other.x < -Eps || (abs(x - other.x) < Eps && y - other.y < -Eps);
    }
    bool operator <= (const point& other) const {
        return *this < other || *this == other;
    }
    bool operator > (const point& other) const {
        return !(*this < other) && !(*this == other);
    }
    bool operator >= (const point& other) const {
        return !(*this < other);
    }
    // Длина вектора
    long double len() const {
        return sqrt(x * x + y * y);
    }
    // Поворот вектора на a радиан(!) (против часовой стрелки)
    point rotate_rad(const long double& a) const {
        return point(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a));
    }
    // Поворот вектора на a градусов(!) (против часовой стрелки)
    point rotate(const long double& a) const {
        return this->rotate_rad(a * pi / 180);
    }
    // Единичный вектор
    point e() const {
        long double len = this->len();
        if (len == 0) return point(0, 0);
        point w(x / len, y / len);
        return w;
    }
    // Вектор, перпендикулярный данному
    point n() const {
        return point(y, -x);
    }
    bool isZero() const {
        return x < Eps && y < Eps;
    }
}; // Struct point


ostream& operator << (ostream& cout, const point& p) {
    cout << p.x << " " << p.y;
    return cout;
}

istream& operator >> (istream& cin, point& p) {
    cin >> p.x >> p.y;
    return cin;
}

struct line {
    long double a, b, c;
    line() : a(1), b(-1), c(0) {};
    line(const long double&_a,const long double&_b,const long double&_c) : a(_a), b(_b), c(-c) {};
    line(const point& p1, const point& p2) : a(p2.y - p1.y), b(p1.x - p2.x), c(-(a*p1.x + b*p1.y)) {};

    long double calc(const point& p) const {
        return a * p.x + b * p.y + c;
    }

    point n() const {
        return point(a, b);
    }

    point guideVector() const {
        return point(b, -a);
    }

    bool operator == (const line& o) const {
        return abs(a * o.b - o.a * b) < Eps && abs(a * o.c - o.a * c) < Eps && abs(b * o.c - o.b * c) < Eps;
    }

    bool operator || (const line& o) const {
        return abs(a * o.b - o.a * b) < Eps;
    }
}; // Struct line

ostream& operator << (ostream& cout, const line& l) {
    cout << l.a << " " << l.b << " " << l.c;
    return cout;
}

istream& operator >> (istream& cin, line& l) {
    cin >> l.a >> l.b >> l.c;
    return cin;
}

// Точка пересечения прямых без проверки на параллельность
point crossLines(const line& L1, const line& L2) {
    point w;
    long double d = L1.a * L2.b - L1.b * L2.a; // Точек пересечения 0 или бесконечность при d ~ 0
    w.x = (L2.c * L1.b - L1.c * L2.b) / d;
    w.y = (L1.c * L2.a - L1.a * L2.c) / d;
    return w;
}

point fromPointToLine(const point& p, const line& l) {
    long double len = abs(l.calc(p)) / sqrt(l.a*l.a + l.b*l.b);
    point w = l.n().e() * len;
    if (abs(l.calc(p + w)) > Eps) {
        return point(0, 0) - w;
    }
    return w;
}

struct circle {
    point center;
    long double radius;
    circle() : center(point(0, 0)), radius(1) {};
    circle(const point& p, const long double& r) : center(p), radius(r) {};
    circle(const long double& x, const long double& y, const long double& r) : center(point(x, y)), radius(r) {};

    bool operator < (const circle& other) const {
        return center < other.center || center == other.center && radius < other.radius;
    }
};

bool isPointInCircle(const point& p, const circle& c) {
    return (p - c.center).len() - c.radius < Eps;
}

bool isCrossingCircleAndLine(const circle& C, const line& L) {
    return fromPointToLine(C.center, L).len() <= C.radius;
}

// Точки пересечения окружности с прямой (без обработки их отсутствия)
pair<point,point> crossCircleAndLine(const circle& C, const line& L) {
    point h = fromPointToLine(C.center, L);
    long double x = sqrt(C.radius*C.radius - h.len()*h.len());
    point x1 = L.guideVector().e() * x;
    point x2 = L.guideVector().e() * -x;
    return make_pair(C.center+h+x1, C.center+h+x2);
}

bool isCrossingCircles(const circle& C1, const circle& C2) {
    long double l = (C1.center - C2.center).len();
    return (C2.radius - l - C1.radius < Eps) && (C1.radius - l - C2.radius < Eps) && (C1.radius + C2.radius - l > Eps);
}

pair<point,point> crossCircles(const circle& c1, const circle& c2) {
    point d = c1.center - c2.center;
    // a - угол между вектором d и вектором, идущим из центра с2 в точку пересечения
    long double cos_a = (d.len()*d.len() + c2.radius*c2.radius - c1.radius*c1.radius) / (2 * d.len() * c2.radius);
    point d1 = d.e() * c2.radius * cos_a;
    long double x = sqrt(c2.radius*c2.radius - d1.len()*d1.len());
    return make_pair(c2.center + d1 + d.n().e()*x, c2.center + d1 - d.n().e()*x);
}

int sgn(const long double& a) {
    if (a > Eps) return 1;
    if (a < -Eps) return -1;
    return 0;
}

bool isInSameSide(const line& l, const point& a, const point& b) {
    return l.calc(a) * l.calc(b) > 0;
}

int ooo() {
    freopen("input.txt", "r", stdin);

    point p1, p2, p3, p4;
    cin >> p1 >> p2 >> p3 >> p4;

    if (p1 > p2) {
        swap(p1, p2);
    }
    if (p3 > p4) {
        swap(p3, p4);
    }

    point p12 = p2 - p1;
    point p34 = p4 - p3;

    if (p12.isZero()) {
        if ((p3 - p1) || (p4 - p1)) {
            if (p1 >= p3 && p1 <= p4) {
                cout << p1;
            }
            else {
                cout << "Empty";
            }
        }
        else if (p34.isZero()) {
            if (p1 == p3) {
                cout << p1;
            }
            else {
                cout << "Empty";
            }
        }
        else {
            cout << "Empty";
        }
        return 0;
    }

    if (p34.isZero()) {
        if ((p1 - p3) || (p2 - p3)) {
            if (p3 >= p1 && p3 <= p2) {
                cout << p3;
            }
            else {
                cout << "Empty";
            }
        }
        else {
            cout << "Empty";
        }
        return 0;
    }

    line l12(p1, p2);
    line l34(p3, p4);
    if (l12 == l34) {
        if (p2 == p3) {
            cout << p2;
        }
        else if (p4 == p1){
            cout << p1;
        }
        else if (p1 <= p3 && p3 <= p2 || p3 <= p1 && p1 <= p4) {
            if (p1 > p3) {
                cout << p1;
            }
            else {
                cout << p3;
            }
            cout << "\n";
            if (p2 < p4) {
                cout << p2;
            }
            else {
                cout << p4;
            }
            cout << "\n";
        }
        else {
            cout << "Empty";
        }
    }
    else if (p12 || p34) {
        cout << "Empty";
    }
    else {
        int sgn_12_13 = sgn(p12 % (p3 - p1));
        if (sgn_12_13 == 0) {
            cout << p3;
            return 0;
        }
        int sgn_12_14 = sgn(p12 % (p4 - p1));
        if (sgn_12_14 == 0) {
            cout << p4;
            return 0;
        }
        if (sgn_12_13 * sgn_12_14 == 1) {
            cout << "Empty";
            return 0;
        }
        int sgn_34_31 = sgn(p34 % (p3 - p1));
        if (sgn_34_31 == 0) {
            cout << p1;
            return 0;
        }
        int sgn_34_32 = sgn(p34 % (p3 - p2));
        if (sgn_34_32 == 0) {
            cout << p2;
            return 0;
        }
        if (sgn_34_31 * sgn_34_32 == 1) {
            cout << "Empty";
            return 0;
        }
        point res = crossLines(l12, l34);
        cout << res;
    }

    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);

    point a(-1, 1);
    point b(1, 0);

    cout << a*b << endl << a%b;
}