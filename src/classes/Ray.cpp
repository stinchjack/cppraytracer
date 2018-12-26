#include "Ray.hpp"

Ray::Ray () {
  //this->start = Point ();
  //this->direction = Vector ();
}

Ray::Ray (const Point& start, const Vector& direction) {
  this->start[0] = start[0];
  this->start[1] = start[1];
  this->start[2] = start[2];

  this->direction = direction;
}


/*modifies Ppint &p in place*/
Point & Ray::calcPos(FLOAT t, Point &p) {
  p[0] = start[0] + (direction.x * t);
  p[1] = start[1] + (direction.y * t);
  p[2] = start[2] + (direction.z * t);

  return p;
}
