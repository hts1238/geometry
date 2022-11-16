# **Geometry by @futau**

# Namespase `D2` for 2D objects

Located in `headers/geom2d.h`

## **D2::Point**

`D2::Point` is a point in 2D, it has `x` and `y` coordinates.

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

`D2::Line` is a line in 2D, it has `a`, `b` and `c` factors which describe an equation like `ax + by + c = 0`.

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

## **D2::Segment**

`D2::Segment` is a segment in 2D, it has `p1` and `p2` which are two endpoints.

Let `s` to be `D2::Segment` then you can do following:

* get length: `s.len()` and receive `long double`,
* check if it zero: `s.isZero()` and receive `bool`,
* get line containig the segment: `s.getLine()` and receive `D2::Line`,
* get vector: `s.getVector()` and receive `D2::Point` *(any of two directions)*.

## **Function for 2D objects**

### **D2::isCrossingLines**

`D2::isCrossingLines` required two `D2::Line`. Function checks if they intersect and returns `bool` *(`true` if they intersect and `false` otherwise)*

### **D2::crossLines**

`D2::crossLines` required two `D2::Line`. Function finds the point of intersection and returns it. *It returns non-existen point if there're not any intersection points.*
