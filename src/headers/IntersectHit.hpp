#ifndef INTERSECTHIT_HPP
#define INTERSECTHIT_HPP

#include <memory>
#include <map>
#include "Ray.hpp"
#include <stdexcept>

class Shape;

using namespace std;




class IntersectHit {
    Shape *shape;

    IntersectHit (Shape *shape, FLOAT t);

    bool hasShapePoint  = false;
    bool hasShapeNormal = false;
    bool hasWorldRay = false;
    bool hasWorldPoint = false;

    bool hasShapeRay = false;
    bool hasHitPoint = false;


    Point shapePoint; // the hit point in shape-space
    Vector shapeNormal; // the hit normal in shape-space
    Ray worldRay; // the original ray
    Ray shapeRay;
    Point worldPoint;
    FLOAT t;

  public:

    void getWorldPoint(Point &p);
    void setWorldRay(Ray &worldRay);
    void getWorldRay();
    void setShapeRay(Ray &shapeRay);
    void getShapeRay();

    Vector getShapeNormal() ;
    void getShapePoint(Point &p);



};


#endif
