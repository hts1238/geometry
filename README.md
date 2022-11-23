# **Geometry by [@futau](https://futau.t.me)**

# Namespase `D2` for 2D objects

Located in [headers/geom2d.h](https://github.com/hts1238/geometry/blob/master/headers/geom2d.h)

## **D2::Point**

`D2::Point` is a point in 2D, it has `x` and `y` coordinates.

You can create `D2::Point` by the following ways:

* by default: `D2::Point()` returns `(0, 0)` existen point,
* by two `long double` coordinates: `D2::Point(long double x, long double y)` returns `(x, y)` existen point,
* by one `bool` flag: `D2::Point(bool exist)` returns `(0, 0)` existen point if `exist` equals `true` and non-existen point otherwise,
* by two `long double` coordinates and one `bool` flag: `D2::Point(long double x, long double y, bool exist)` returns `(x, y)` existen point if `exist` equals `true` and non-existen point otherwise.

Let `p` to be `D2::Point` then you can do following:

* get coordinates: `p.x` or `p.y` and receive `long double`,
* get length: `p.len()` and receive `long double`,
* get lenght in square: `p.len2()` and receive `long double`,
* get unit vector: `p.e()` and receive `D2::Point` *(same vector but length 1)*,
* get perpendicular vector: `p.n()` and receive `D2::Point` *(the same length, but the turns may differ in different quarters of the plane)*,
* check for zero vector: `p.isZero()` and receive `bool`,
* check if it exists: `p.exist()` *(recommended)* or `p.ex` and receive `bool` *(the cases where the point may not exist will be described below)*. If you try to use or output non-existen vector you catch `std::logic_error("Error: Point does not exist in <...>")`.

Let `p1` and `p2` to be `D2::Point` then you can do following:

* get sum: `p1 + p2` and receive `D2::Point`,
* get difference: `p1 - p2` and receive `D2::Point`,
* get scalar product: `p1 * p2` and receive `long double`,
* get vector product: `p1 % p2` and receive `long double`,
* check for parallelism: `p1 || p2` and receive `bool`,
* compare it:
    * `p1 == p2`,
    * `p1 != p2`,
    * `p1 < p2`,
    * `p1 <= p2`,
    * `p1 > p2`,
    * `p1 >= p2`
    and receive `bool`,
* get rotation angle: `p1.getAngle(p2)` and receive `float` in radians included in (-pi; pi] *(positive if counterclockwise rotation from `p1` to `p2`)*.

Let `a` to be `long double` then you can do following:
* get multiplied vector: `p * a` and receive `D2::Point`,
* get divided vector: `p / a` and receive `D2::Point`,
* get rotated vector: `p.rotate(a)` *(in degrees)* or `p.rotate_rad(a)` *(in radians)* and receive `D2::Point`.

## **D2::Line**

`D2::Line` is a line in 2D, it has `a`, `b` and `c` factors which describe an equation like `a*x + b*y + c = 0`.

You can create `D2::Line` by the following ways:

* by default: `D2::Line()` returns `x - y = 0` line,
* by three `long double` factors: `D2::Line(long double a, long double b, long double c)` returns `a*x + b*y + c = 0` line,
* by two `D2::Point` points: `D2::Line(D2::Point p1, D2::Point p2)` returns line which contains points given.

Let `l` to be `D2::Line` then you can do following:

* get perpendicular vector: `l.n()` and receive `D2::Point` *(any length and any of two directions)*,
* get guide vector: `l.guideVector()` and receive `D2::Point` *(any length and any of two directions)*,
* check if it exist: `l.exist()` or `l.isZero()` *(`true` if `a` and `b` are zero so line does not exist)* and receive `bool`.

Let `l1` and `l2` to be `D2::Line` then you can do following:

* compare it: `l1 == l2` and receive `bool`,
* check for parallelism: `l1 || l2` and receive `bool`.

There are `Ox` and `Oy` constant lines which correspond to the coordinate axes.

## **D2::Circle**

`D2::Circle` is a circle in 2D, it has `center` and `radius`.

You can create `D2::Circle` by the following ways:

* by default: `D2::Circle()` returns circle with the center in `(0, 0)` point and the radius equals `1`,
* by point and radius: `D2::Circle(D2::Point center, long double radius)` returns circle with the center in `center` point and the radius equals `radius`,
* by three numbers: `D2::Circle(long double x, long double y, long double r)` returns circle with the center in `(x, y)` point and the radius equals `r`.

## **D2::Segment**

`D2::Segment` is a segment in 2D, it has `p1` and `p2` which are two endpoints.

You can create `D2::Segment` by the following ways:

* by default: `D2::Segment()` returns segment from (0, 0) point to (1, 1) point,
* by two endpoints: `D2::Circle(D2::Point p1, D2::Point p1)` returns segment from `p1` point to `p2` point.

Let `s` to be `D2::Segment` then you can do following:

* get length: `s.len()` and receive `long double`,
* check if it zero: `s.isZero()` and receive `bool`,
* get line containig the segment: `s.getLine()` and receive `D2::Line`,
* get vector: `s.getVector()` and receive `D2::Point` *(any of two directions)*.

## **Function for 2D objects**

### **D2::isCrossingLines**

`D2::isCrossingLines` requires two `D2::Line`. Function checks if they intersect and returns `bool` *(`true` if they intersect and `false` otherwise). It's worth nothing that `false` is always returned if the lines are equal.*

### **D2::crossLines**

`D2::crossLines` requires two `D2::Line`. Function finds the point of intersection and returns `D2::Point`. *It returns non-existen point if there're not any intersection points or lines are equal.*

### **D2::fromPointToLine**

`D2::fromPointToLine` requires `D2::Point` and `D2::Line`. Function finds the shortest vector from the point to the line and returns `D2::Point`. *It returns non-existen point if the line does not exist.*

### **D2::isPointInCircle**

`D2::isPointInCircle` requires `D2::Point` and `D2::Circle`. Function checks if the point is inside or on the border of the circle and returns `bool` *(`true` if it is and `false` otherwise).*

### **D2::isCrossingCircleAndLine**

`D2::isCrossingCircleAndLine` requires `D2::Circle` and `D2::Line`. Function checks if they intersect and returns `bool` *(`true` if they intersect and `false` otherwise).*

### **D2::crossCircleAndLine**

`D2::crossCircleAndLine` requires `D2::Circle` and `D2::Line`. Function finds the points where they intersect and returns `std::pair<D2::Point, D2::Point>`. *It returns pair of two non-existen points if there're not any intersection points and returns pair of two equal points if there're only one intersection point.*

### **D2::isCrossingCircles**

`D2::isCrossingCircles` requires two `D2::Circle`. Function checks if they intersect and returns `bool` *(`true` if they intersect and `false` otherwise).*

### **D2::crossCircles**

`D2::crossCircles` requires two `D2::Circle`. Function finds the points where they intersect and returns `std::pair<D2::Point, D2::Point>`. *It returns pair of two non-existen points if there're not any intersection points and returns pair of two equal points if there're only one intersection point.*

### **D2::isInSameSide**

`D2::isInSameSide` requires `D2::Line` and two `D2::Point`. Function checks if the points are in the same side of the line including the line itself and returns `bool` *(`true` if it is and `false` otherwise). It's worth nothing that `true` is always returned if at least one point is on the line itself.*

### **D2::isInSameSideExcluding**

`D2::isInSameSideExcluding` requires `D2::Line` and two `D2::Point`. Function checks if the points are in the same side of the line excluding the line itself and returns `bool` *(`true` if it is and `false` otherwise). It's worth nothing that `false` is always returned if at least one point is on the line itself.*

### **D2::isPointInSegment**

`D2::isPointInSegment` requires `D2::Segment` and `D2::Point`. Function checks if the point is in the segment including endpoints and returns `bool` *(`true` if it is and `false` otherwise).*

### **D2::isCrossingSegments**

`D2::isCrossingSegments` requires two `D2::Segment`. Function checks if they intersect including endpoints and returns `bool` *(`true` if they intersect and `false` otherwise). It's worth nothing that `false` is always returned if there're more than one intersection points.*

### **D2::crossSegments**

`D2::crossSegments` requires two `D2::Segment`. Function finds the point of intersection including endpoints and returns `D2::Point`. *It returns non-existen point if there're not any intersection points or there're more than one intersection points.*

<hr>
© 2018-2022 Timur Khalikshin

Contact: [Telegram](https://futau.t.me), [Email](mailto:hts1238@mail.ru)
