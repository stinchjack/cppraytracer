#ifndef RAY_HPP
#define RAY_HPP

#include "Point.hpp"
#include "Vector.hpp"
#include <memory>

class Ray;


using namespace std;

typedef shared_ptr<Ray> RayPtr;



class Ray {

  public:


  Point start;
  Vector direction;
  bool isShadowRay = false;

  bool startIsEye = false;

  inline Ray(){};

  inline Ray(const Point& start, const Vector& direction);
  inline Ray(const Point& start, FLOAT vx, FLOAT vy, FLOAT vz);

  Point calcPos(FLOAT t);

  Vector reflection (Vector &normal);
};


inline RayPtr makeRayPtr(const Point& start, const Vector& direction) {
  return make_shared<Ray>(start, direction);
}

Ray::Ray (const Point& start, const Vector& direction) {
  this->start = start;
  this->direction = direction;

}

Ray::Ray (const Point& start, FLOAT vx, FLOAT vy, FLOAT vz) {
  this->start = start;
  this->direction = Vector(vx, vy, vz);

}



#endif
