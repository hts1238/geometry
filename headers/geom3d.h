#ifndef GEOM_3D_HEADER
#define GEOM_3D_HEADER

#include <iostream>
#include <cmath>

using namespace std;

namespace D3 {
    const long double pi = acos(-1);
    const long double Eps = 1e-9;
    const string __beg__ = "(", __sep__ = ";", __end__ = ")";
    const string __lot__ = "xyz"; // [ default=xyz | xyz | numbers ]
    const string __form_sep__ = " ";

    struct Point {
        long double x, y, z;
        Point() : x(0), y(0), z(0) {};
        Point(long double _x, long double _y, long double _z) : x(_x), y(_y), z(_z) {};
    };

    ostream& operator << (ostream& cout, const Point& p) {
        cout << __beg__ << p.x << __sep__ << p.y << __sep__ << p.z << __end__;
        return cout;
    }

    istream& operator >> (istream& cin, Point& p) {
        cin >> p.x >> p.y >> p.z;
        return cin;
    }

    struct Vector {
        long double x, y, z;
        Vector() : x(0), y(0), z(0) {};
        Vector(long double _x, long double _y, long double _z) : x(_x), y(_y), z(_z) {};

        // Сложение векторов
        Vector operator + (const Vector& other) const {
            return Vector(x + other.x, y + other.y, z + other.z);
        }
        // Вычитание векторов
        Vector operator - (const Vector& other) const {
            return Vector(x - other.x, y - other.y, z - other.z);
        }
        // Скалярное произведение векторов
        long double operator * (const Vector& other) const {
            return x * other.x + y * other.y + z * other.z;
        }
        // Растягивание вектора
        Vector operator * (const long double& a) const {
            return Vector(x * a, y * a, z * a);
        }
        // Сжатие вектора
        Vector operator / (const long double& a) const {
            return Vector(x / a, y / a, z / a);
        }
        // Векторное произведение векторов
        Vector operator % (const Vector& other) const {
            return Vector(
                y * other.z - z * other.y,
                z * other.x - z * other.x,
                x * other.y - y * other.x
            );
        }
        // Проверка на параллельность векторов
        bool operator || (const Vector& other) const {
            return this->isZero() || other.isZero() || (*this % other).len() < Eps;
        }
        bool operator == (const Vector& other) const {
            return abs(x - other.x) < Eps && abs(y - other.y) < Eps && abs(z - other.z) < Eps;
        }
        bool operator != (const Vector& other) const {
            return !(*this == other);
        }
        bool operator < (const Vector& other) const {
            return x - other.x < -Eps || (abs(x - other.x) < Eps && y - other.y < -Eps) || (abs(x - other.x) < Eps && abs(y - other.y) < Eps && z - other.z < -Eps);
        }
        bool operator <= (const Vector& other) const {
            return *this < other || *this == other;
        }
        bool operator > (const Vector& other) const {
            return !(*this < other) && !(*this == other);
        }
        bool operator >= (const Vector& other) const {
            return !(*this < other);
        }
        // Длина вектора
        long double len() const {
            return sqrt(x * x + y * y + z * z);
        }
        // Длина вектора в квадрате
        long double len2() const {
            return x * x + y * y + z * z;
        } 
        /*// Поворот вектора на a радиан(!) (против часовой стрелки)
        Vector rotate_rad(const long double& a) const {
            return Vector(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a));
        }
        // Поворот вектора на a градусов(!) (против часовой стрелки)
        Vector rotate(const long double& a) const {
            return this->rotate_rad(a * pi / 180);
        }*/
        // Единичный вектор
        Vector e() const {
            if (this->isZero()) return Vector();
            long double len = this->len();
            return Vector(x / len, y / len, z / len);
        }
        /*// Вектор, перпендикулярный данному
        Vector n() const {
            return Vector(y, -x);
        }*/
        bool isZero() const {
            return abs(x) < Eps && abs(y) < Eps && abs(z) < Eps;
        }
    };

    ostream& operator << (ostream& cout, const Vector& p) {
        cout << __beg__ << p.x << __sep__ << p.y << __sep__ << p.z << __end__;
        return cout;
    }

    istream& operator >> (istream& cin, Vector& p) {
        cin >> p.x >> p.y >> p.z;
        return cin;
    }

    struct Plane {
        long double a, b, c, d;
        Plane() : a(1), b(-1), c(0), d(0) {};
        Plane(const long double& _a, const long double& _b, const long double& _c, const long double& _d) : a(_a), b(_b), c(_c), d(_d) {};
        Plane(const Point& p1, const Vector& p2) : // p1 - точка на прямой, p2 - направляющий вектор
            a(p2.y - p2.z),
            b(p2.z - p2.x),
            c(p2.x - p2.y),
            d(-a*p1.x -b*p1.y -c*p1.z)
        {};

        /*long double calc(const Vector& p) const {
            return a * p.x + b * p.y + c;
        }/*

        /*Vector n() const {
            return Vector(a, b, c);
        }*/

        /*Vector guideVector() const {
            return Vector(b, -a);
        }*/

        /*bool operator == (const Plane& o) const {
            return abs(a * o.b - o.a * b) < Eps && abs(a * o.c - o.a * c) < Eps && abs(b * o.c - o.b * c) < Eps;
        }*/

        /*bool operator || (const Plane& o) const {
            return abs(a * o.b - o.a * b) < Eps;
        }*/
    }; // Struct Plane

    ostream& operator << (ostream& cout, const Plane& l) {
        if (__lot__ == "numbers") {
            cout << __beg__ << l.a << __sep__ << l.b << __sep__ << l.c << __sep__ << l.d << __end__;
        }
        else {
            bool isPrinted = false;

            if (l.a == 0 && l.b == 0 && l.c == 0 && l.d == 0) {
                cout << 0;
                isPrinted = true;
            }
            else if (l.a != 0) {
                if (l.a != 1) {
                    cout << l.a;
                }
                cout << "x";
                isPrinted = true;
            }


            if (l.b < -Eps) {
                if (isPrinted) {
                    cout << __form_sep__;
                }
                cout << l.b << "y";
                isPrinted = true;
            }
            else if (l.b == 1) {
                if (isPrinted) {
                    cout << __form_sep__;
                }
                cout << "y";
                isPrinted = true;
            }
            else if (l.b > Eps) {
                if (isPrinted) {
                    cout << __form_sep__ << "+" << __form_sep__;
                }
                cout << l.b << "y";
                isPrinted = true;
            }

            if (l.c < -Eps) {
                if (isPrinted) {
                    cout << __form_sep__;
                }
                cout << l.c << "z";
                isPrinted = true;
            }
            else if (l.c == 1) {
                if (isPrinted) {
                    cout << __form_sep__;
                }
                cout << "z";
                isPrinted = true;
            }
            else if (l.c > Eps) {
                if (isPrinted) {
                    cout << __form_sep__ << "+" << __form_sep__;
                }
                cout << l.c << "z";
                isPrinted = true;
            }

            if (l.d < -Eps) {
                if (isPrinted) {
                    cout << __form_sep__;
                }
                cout << l.d;
                isPrinted = true;
            }
            else if (l.d > Eps) {
                if (isPrinted) {
                    cout << __form_sep__ << "+" << __form_sep__;
                }
                cout << l.d;
                isPrinted = true;
            }
            cout << __form_sep__ << "=" << __form_sep__ << "0";
        }
        return cout;
    }

    istream& operator >> (istream& cin, Plane& l) {
        cin >> l.a >> l.b >> l.c >> l.d;
        return cin;
    }
}

#endif
