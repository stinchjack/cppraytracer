
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
    inline Point(){};
    inline Point (FLOAT x, FLOAT y, FLOAT z);
    Point (Vector &v);
    inline Point (const Point &p);

    inline Point& operator+=(const Point &rhs);
    inline Point& operator-=(const Point &rhs);
    inline Point operator+(const Point &rhs) const;
    Point operator+(const Vector &rhs) const;
    Point operator-(const Vector &rhs) const;
    inline Point operator-(const Point &rhs) const;
    inline FLOAT operator*(Point &rhs) const;
    FLOAT operator*(Vector &rhs) const;

};

// inline functions need to be in header file

Point::Point(FLOAT x, FLOAT y, FLOAT z) {
  this->x=x;
  this->y=y;
  this->z=z;
}

Point::Point (const Point &p) {
  x = p.x;
  y = p.y;
  z = p.z;
}

Point& Point::operator+=(const Point &rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

Point& Point::operator-=(const Point &rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  return *this;
}

Point Point::operator+(const Point &rhs)  const
{
  return Point (x + rhs.x, y + rhs.y, z + rhs.z);
}


Point Point::operator-(const Point &rhs)  const
{
return Point (x - rhs.x, y - rhs.y, z - rhs.z);
}

FLOAT Point::operator*(Point &rhs) const
{

  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);

}



#endif
