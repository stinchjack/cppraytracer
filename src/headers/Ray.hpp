#ifndef RAY_HPP
#define RAY_HPP

#include "Point.hpp"
#include "Vector.hpp"

class Ray {
  private:
    Point start;
    Vector direction;

  public:

  Ray(const Point& start, const Vector& direction);
  Point calcPos(FLOAT t);


};

Ray::Ray (const Point& start, const Vector& direction) {
  this->start = Point (start);
  this->direction = Vector (direction);
}

FLOAT Ray::calcPos(FLOAT t) {
  return Point (start.x + (direction.x * t),  start.y + (direction.y * t), start.z + (direction.z * t))
}

#endif


/*
FLOAT interesectPoint[3];
Ray.calcPos(interesectPoint, t)

Point Ipos = Ray.calcpos(t)
*/
