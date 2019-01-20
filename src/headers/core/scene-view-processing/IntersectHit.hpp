#ifndef INTERSECTHIT_HPP
#define INTERSECTHIT_HPP

#include <memory>
#include <map>
#include "Ray.hpp"
#include <stdexcept>

class Scene;
class Shape;

using namespace std;

class IntersectHit;

typedef shared_ptr<IntersectHit> IHPtr;
typedef shared_ptr<IntersectHit> IntersectHitPtr;

class IntersectHit {
  private:
    Shape *shape = 0;


    bool hasShapePoint  = false;
    bool hasShapeNormal = false;
    bool hasWorldNormal = false;
    bool hasWorldRay = false;
    bool hasWorldPoint = false;

    bool hasShapeRay = false;
    bool hasHitPoint = false;


    Point shapePoint; // the hit point in shape-space
    Vector shapeNormal; // the hit normal in shape-space
    Vector worldNormal; // the hit normal in shape-space
    Ray worldRay; // the original ray
    Ray shapeRay;
    Point worldPoint;
    FLOAT t;

  public:
    Scene *scene = 0;

    inline IntersectHit (){};
    inline IntersectHit (Shape *shape, FLOAT t);
    IntersectHit (const IntersectHitPtr ih);
    Point getShapePoint();
    Point getWorldPoint();
    void setWorldRay(Ray &worldRay);
    Ray getWorldRay();
    void setShapeRay(Ray &shapeRay);
    void setShapePoint(Point &p);
    Ray getShapeRay();
    Shape *getShape();

    Vector getShapeNormal() ;
    Vector getWorldNormal() ;




};

IntersectHit::IntersectHit (Shape *shape, FLOAT t) {
  this->shape = shape;
  this->t = t;
}


#endif
