#ifndef RAY_HPP
#define RAY_HPP

#include "Point.hpp"
#include "Vector.hpp"

class Ray {

  public:
  Point start;
  Vector direction;

  Ray();

  Ray(const Point& start, const Vector& direction);

  /*
  Ray::calcPos modifies p in place
  */
  Point & calcPos(FLOAT t, Point &p) ;


};


#endif
