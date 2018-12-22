#include "Ray.hpp"

Ray::Ray () {
  //this->start = Point ();
  //this->direction = Vector ();
}

Ray::Ray (const Point& start, const Vector& direction) {
  this->start = start;
  this->direction = direction;
}

Point Ray::calcPos(FLOAT t) {
  return Point (start.x + (direction.x * t),  start.y + (direction.y * t), start.z + (direction.z * t));
}
