#include "Point.hpp"

#include "Vector.hpp"



/*Point operator+(const Point &lhs, const Point &rhs)
{
  return {lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]};
}*/


/*FLOAT operator*(Point &lhs, Vector &rhs) // dot product
{

  return (lhs[0] * rhs.x) + (lhs[1] * rhs.y) + (lhs[2] * rhs.z);

}*/

FLOAT dot (Point &lhs, Point &rhs) // dot product
{

  return (lhs[0] * rhs[0]) + (lhs[1] * rhs[1]) + (lhs[2] * rhs[2]);

}

/*
Point::Point() {
  x=0;
  y=0;
  z=0;*
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

Point Point::operator-(const Point &rhs)
{
  Point p;

  p.x = x - rhs.x;
  p.y = y - rhs.y;
  p.z = z - rhs.z;

  return p;
}

FLOAT Point::operator*(Point &rhs)
{

  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);

}

FLOAT Point::operator*(Vector &rhs)
{

  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);

}*/
