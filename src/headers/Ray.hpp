#ifndef RAY_HPP
#define RAY_HPP

#include "Point.hpp"
#include "Vector.hpp"

class Ray {
  private:


  public:
  Ray(FLOAT *point, Vector &direction);

  FLOAT *  calcPos(FLOAT t);

};

FLOAT Ray::calcPos() {
  static FLOAT point[3];
  point[0] = 
}

#endif


/*
FLOAT interesectPoint[3];
Ray.calcPos(interesectPoint, t)

Point Ipos = Ray.calcpos(t)
*/
