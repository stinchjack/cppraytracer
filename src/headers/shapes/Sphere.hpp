#ifndef SPHERE_HPP
#define SPHERE_HPP

#include  "Shape.hpp"

class Sphere;

typedef shared_ptr<Sphere> SpherePtr;

class Sphere: public Shape {
public:
  Sphere();
  void shapeTestIntersect (QueueItemResults &results, Ray &ray, Ray &worldRay);
  virtual Vector getShapeNormal(IntersectHit *ih);
};

#endif
