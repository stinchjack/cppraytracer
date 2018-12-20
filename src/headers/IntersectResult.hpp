#ifndef INTERSECTRESULT_HPP
#define INTERSECTRESULT_HPP

#include <memory>
#include <map>
#include "Ray.hpp"

class Shape;

using namespace std;



class IntersectHit {

  public:

    IntersectHit();
    IntersectHit(Ray &ray, Shape *sh);
    IntersectHit(Ray &ray, Point &raw_point, Point &raw_normal, Shape *sh);

    Shape *shape;
    Ray ray;
    Point raw_point;
    Point raw_normal;
};

#endif
