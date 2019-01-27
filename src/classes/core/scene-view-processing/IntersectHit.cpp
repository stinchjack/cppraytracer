#include "IntersectHit.hpp"
#include "Shape.hpp"
#include <iostream>

  IntersectHit::IntersectHit (const IntersectHitPtr ih) {
    hasShapePoint  = ih->hasShapePoint;
    hasShapeNormal = ih->hasShapeNormal;
    hasWorldNormal = ih->hasWorldNormal;
    hasWorldRay = ih->hasWorldRay;
    hasWorldPoint = ih->hasWorldPoint;

    hasShapeRay = ih->hasShapeRay;
    hasHitPoint = ih->hasHitPoint;


    shapePoint =  ih->shapePoint;


    shapeNormal=  ih->shapeNormal;
    worldNormal=  ih->worldNormal;


    worldRay =  ih->worldRay;
    shapeRay = ih->shapeRay;
    worldPoint = ih->worldPoint;

    t = ih->t;
  }

  Shape *IntersectHit::getShape() {
    return shape;
  }


  Point IntersectHit::getWorldPoint() {
    if (!hasWorldPoint) {
      if (!hasWorldRay) {
        throw std::logic_error( "No world ray set" );
      }
      worldPoint = worldRay.calcPos(t);
      hasWorldPoint = true;
    }
    return  worldPoint;
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



  Vector IntersectHit::getWorldNormal() {

      if (!hasWorldNormal) {
        if(!hasShapeNormal) {
            shapeNormal = shape->getShapeNormal(this);
            hasShapeNormal = true;
        }
        worldNormal = shape->transformation.inverseTransform(shapeNormal);
      }
      return worldNormal;
  }


  Vector IntersectHit::getShapeNormal() {

      if(!hasShapeNormal) {
          shapeNormal = shape->getShapeNormal(this);
          hasShapeNormal = true;
      }
      return shapeNormal;
  }

  Point IntersectHit::getShapePoint() {
    if (!hasShapePoint) {
      if (!hasShapeRay) {
        throw std::logic_error( "No shape ray set" );
      }
      shapePoint = shapeRay.calcPos(t);
      hasShapePoint = true;

    }

    return shapePoint;

  }


void IntersectHit::setShapePoint(Point &p) {
  shapePoint = p;
  hasShapePoint = true;
}
