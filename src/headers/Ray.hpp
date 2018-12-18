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
  Point calcPos(FLOAT t);


};


#endif


/*
FLOAT interesectPoint[3];
Ray.calcPos(interesectPoint, t)

Point Ipos = Ray.calcpos(t)
*/
