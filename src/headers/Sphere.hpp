#ifndef SPHERE_HPP
#define SPHERE_HPP

#include  "Shape.hpp"

SHAPE_PTR SpherePtr();

class Sphere: public Shape {

  map<int, IntersectHit> testIntersect (Ray &ray);
};

#endif
