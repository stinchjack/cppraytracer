#ifndef SQUARE_HPP
#define SQAURE_HPP

#include  "Shape.hpp"
#include <iostream>
SHAPE_PTR SquarePtr();
SHAPE_PTR SquarePtr(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom);
class Square;

typedef Square Square;

class Square: public Shape {

  Vector normal = Vector(0,0,1);
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
