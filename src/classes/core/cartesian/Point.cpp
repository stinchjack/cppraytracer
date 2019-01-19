#include "Point.hpp"
#include "Vector.hpp"

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

Point::Point (Vector &v) {
  x = v.x;
  y = v.y;
  z = v.z;
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



Point Point::operator+(const Vector &rhs)  const
{
  return Point (x + rhs.x, y + rhs.y, z + rhs.z);
}

Point Point::operator-(const Vector &rhs)  const
{
  return Point (x - rhs.x, y - rhs.y, z - rhs.z);
}

Point Point::operator-(const Point &rhs)  const
{
return Point (x - rhs.x, y - rhs.y, z - rhs.z);
}

FLOAT Point::operator*(Point &rhs) const
{

  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);

}

FLOAT Point::operator*(Vector &rhs) const
{

  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);

}
