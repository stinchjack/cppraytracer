#ifndef RAY_HPP
#define RAY_HPP

#include "Point.hpp"
#include "Vector.hpp"
class Ray;
typedef shared_ptr<Ray> RayPtr;

class Ray {

  public:

  static inline makePtr(const Point& start, const Vector& direction);

  Point start;
  Vector direction;
  bool isShadowRay = false;

  bool startIsEye = false;

  inline Ray(){};

  inline Ray(const Point& start, const Vector& direction);
  inline Ray(const Point& start, FLOAT vx, FLOAT vy, FLOAT vx);

  Point calcPos(FLOAT t);

  Vector reflection (Vector &normal);
};


RayPtr makePtr(const Point& start, const Vector& direction) {
  return make_shared<Ray>(start, direction);
}

Ray::Ray (const Point& start, const Vector& direction) {
  this->start = start;
  this->direction = direction;

}

Ray::Ray (const Point& start, FLOAT vx, FLOAT vy, FLOAT vx) {
  this->start = start;
  this->direction = Vector(vx, vy, vz);

}



#endif
