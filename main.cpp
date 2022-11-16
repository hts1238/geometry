#include <iostream>
#include "headers/geom2d.h"
#include "headers/geom3d.h"

using namespace std;

/*int ooo() {
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
}*/

int main() {
    freopen("input.txt", "r", stdin);

    D2::Segment s1(0, 0, 2, 2);
    D2::Segment s2(-1, 0, 0, -1);

    auto res = D2::crossSegments(s1, s2);

    2 * res;
}