#ifndef SPHERE_HPP
#define SPHERE_HPP

#include  "Shape.hpp"

SHAPE_PTR SpherePtr();

class Sphere: public Shape {

  void shapeTestIntersect (QueueItemResults &results, Ray &ray);
};

#endif
