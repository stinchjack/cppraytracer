#ifndef RAY_HPP
#define RAY_HPP

#include "Point.hpp"
#include "Vector.hpp"

class Ray {

  public:
  Point start;
  Vector direction;
  bool isShadowRay = false;
#ifdef EYE_TRANSFORM_SHORTCUT
  bool startIsEye = false;
#endif
  Ray();

  Ray(const Point& start, const Vector& direction);

  Point calcPos(FLOAT t);

  Vector reflection (Vector &normal);
};


#endif