#ifndef INTERSECTRESULT_HPP
#define INTERSECTRESULT_HPP

#include <memory>
#include <map>
#include "Ray.hpp"

class Shape;

using namespace std;




struct IntersectHit {
    Shape *shape;
    Ray worldRay;
    Ray shapeRay;
    FLOAT t;
    bool hasShapePoint;
    bool hasShapeNormal;
    Point shapePoint;
    Vector shapeNormal;
    Point hitPoint;
};


#endif
