#include "Point.hpp"
#include "Float.hpp"

Point::Point() {
  x=0;
  y=0;
  z=0;
}

Point::Point(FLOAT x, FLOAT y, FLOAT z) {
  this->x=x;
  this->y=y;
  this->z=z;
}

Point& Point::operator+=(const Point &rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

Point Point::operator+(const Point &rhs)
{
  Point p;

  p.x = x + rhs.x;
  p.y = y + rhs.y;
  p.z = z + rhs.z;

  return p;
}
