#include "IntersectHit.hpp"
#include "Shape.hpp"

IntersectHit::IntersectHit () {
}

IntersectHit::IntersectHit (Shape *shape, FLOAT t) {
  this->shape = shape;
  this->t = t;
}


  IntersectHit::IntersectHit (const IntersectHit &ih) {
    hasShapePoint  = ih.hasShapePoint;
    hasShapeNormal = ih.hasShapeNormal;
    hasWorldRay = ih.hasWorldRay;
    hasWorldPoint = ih.hasWorldPoint;

    hasShapeRay = hasShapeRay;
    hasHitPoint = hasHitPoint;


    shapePoint[0] =  ih.shapePoint[0];
    shapePoint[1] =  ih.shapePoint[1];
    shapePoint[2] =  ih.shapePoint[2];

    shapeNormal=  ih.shapeNormal;


    worldRay =  ih.worldRay;
    shapeRay = ih.shapeRay;
    worldPoint[0] = ih.worldPoint[0];
    worldPoint[1] = ih.worldPoint[1];
    worldPoint[2] = ih.worldPoint[2];
    t = ih.t;
  }

  Shape *IntersectHit::getShape() {
    return shape;
  }


  void IntersectHit::getWorldPoint(Point &p) {
    if (!hasWorldPoint) {
      if (!hasWorldRay) {
        throw std::logic_error( "No world ray set" );
      }
      worldRay.calcPos(t, worldPoint);
      hasWorldPoint = true;

    }

    p[0] = worldPoint[0];
    p[1] = worldPoint[1];
    p[2] = worldPoint[2];

  }


  void IntersectHit::setWorldRay(Ray &worldRay) {
    this->worldRay = worldRay;
    hasWorldRay = true;
  }

  Ray IntersectHit::getWorldRay() {
    if (!hasWorldRay) {
      throw std::logic_error( "No WorldRay set" );
    }
    return worldRay;
  }

  void IntersectHit::setShapeRay(Ray &shapeRay) {
    this->shapeRay = shapeRay;
    hasShapeRay = true;
  }

  Ray IntersectHit::getShapeRay() {
    if (!hasShapeRay) {
      throw std::logic_error( "No shape ray set" );
    }
    return shapeRay;
  }



  Vector IntersectHit::getShapeNormal() {

      if(!hasShapeNormal) {
          shapeNormal = shape->getShapeNormal(*this);
          hasShapeNormal = true;
      }
      return shapeNormal;
  }

  void IntersectHit::getShapePoint(Point &p) {
    if (!hasShapePoint) {
      if (!hasShapeRay) {
        throw std::logic_error( "No shape ray set" );
      }
      shapeRay.calcPos(t, shapePoint);
      hasShapePoint = true;

    }

    p[0] = shapePoint[0];
    p[1] = shapePoint[1];
    p[2] = shapePoint[2];

  }
