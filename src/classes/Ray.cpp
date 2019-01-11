#include "Ray.hpp"

Ray::Ray () {

}

Ray::Ray (const Point& start, const Vector& direction) {
  this->start = start;
  this->direction = direction;
}


Point Ray::calcPos(const FLOAT t) const {
 return start + (direction * t);
}
