#ifndef INTERSECTRESULT_HPP
#define INTERSECTRESULT_HPP

#include <memory>
#include <map>
#include "Ray.hpp"

class Shape;

using namespace std;

class IntersectResult {
public:
  bool hit = false;

};

class NoIntersect: public IntersectResult {
public:
  bool hit = false;
};

class IntersectHit: public IntersectResult {

  public:

    IntersectHit();
    IntersectHit(Ray &ray);
    IntersectHit(Ray &ray, Point &raw_point, Point &raw_normal);
    Shape *shape;
    Ray ray;
    Point raw_point;
    Point raw_normal;
};

#endif
