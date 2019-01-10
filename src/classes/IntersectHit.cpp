#include "IntersectHit.hpp"


/*
IntersectHit::IntersectHit() {

}

IntersectHit::IntersectHit(Ray &ray, Shape *sh) {
  this->ray = ray;
  this->shape = sh;
}


IntersectHit::IntersectHit(Ray &ray, Point &raw_point, Point &raw_normal, Shape *sh) {

  this->ray = ray;
  this->raw_point = raw_point;
  this->raw_normal = raw_normal;
  this->shape = sh;

}*/

  IntersectHit::IntersectHit (Shape *shape, FLOAT t) {
    this->shape = shape;
    this->t = t;
  }

  void IntersectHit::getWorldPoint(Point &p) {
    if (!hasWorldPoint) {
      if (!hasWorldRay) {
        throw std::logic_error( "No world ray set" );
      }
      shapeRay.calcPos(t, worldPoint);
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

  void IntersectHit::getWorldRay() {
    if (!hasWorldRay) {
      throw std::logic_error( "No WorldRay set" );
    }
    return worldRay;
  }

  void IntersectHit::setShapeRay(Ray &shapeRay) {
    this->shapeRay = shapeRay;
    hasShapeRay = true;
  }

  void IntersectHit::getShapeRay() {
    if (!hasShapeRay) {
      throw std::logic_error( "No shape ray set" );
    }
    return shapeRay;
  }



  Vector IntersectHit::getShapeNormal() {

      if(!hasShapeNormal) {
          shapeNormal = shape->getShapeNormal();
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
