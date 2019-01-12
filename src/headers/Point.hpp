
#ifndef POINT_HPP
#define POINT_HPP

#include "Float.hpp"

#include <math.h>


class Vector;

//typedef FLOAT Point[3];

//FLOAT dot (Point &lhs, Point &rhs);
//FLOAT operator*(Point &lhs, Vector &rhs);


class Point {
  friend class Vector;

  public:

    FLOAT x,y,z;
    Point();
    Point (FLOAT x, FLOAT y, FLOAT z);
    Point (Vector &v);

    Point& operator+=(const Point &rhs);
    Point& operator-=(const Point &rhs);
    Point operator+(const Point &rhs) const;
    Point operator+(const Vector &rhs) const;
    Point operator-(const Vector &rhs) const;
    Point operator-(const Point &rhs) const;
    FLOAT operator*(Point &rhs) const;
    FLOAT operator*(Vector &rhs) const;

};


#endif
