#ifndef INTERSECTRESULT_HPP
#define INTERSECTRESULT_HPP

#include <memory>
#include <map>
#include "Ray.hpp"

class Shape;

using namespace std;



struct IntersectHit {
    Shape *shape;
    Ray ray;
    Point raw_point;
    Point raw_normal;
};

#endif
