#ifndef SQUARE_HPP
#define SQAURE_HPP

#include  "Shape.hpp"

SHAPE_PTR SpherePtr();

class Square: public Shape {

  Vector normal(0,0,-1);
  FLOAT top = -1;
  FLOAT left = -1;
  FLOAT bottom = 1;
  FLOAT right = 1;

public:
  Square ();
  Square (FLOAT left, FLOAT right, FLOAT top, FLOAT bottom);

  void shapeTestIntersect (QueueItemResults &results, Ray &ray, Ray &worldRay);
  virtual Vector getShapeNormal(IntersectHit &ih);
};

#endif
