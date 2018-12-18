#include "Ray.hpp"

Ray::Ray () {
  this->start = Point ();
  this->direction = Vector ();
}

Ray::Ray (const Point& start, const Vector& direction) {
  this->start = Point (start);
  this->direction = Vector (direction);
}

Point Ray::calcPos(FLOAT t) {
  return Point (start.x + (direction.x * t),  start.y + (direction.y * t), start.z + (direction.z * t));
}
