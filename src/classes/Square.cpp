#include  "Square.hpp"
#include <math.h>


SHAPE_PTR SquarePtr() {
  return std::make_shared<Square>();
}

SHAPE_PTR SquarePtr(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom) {
  return std::make_shared<Square> (left, right, top, bottom);
}



Square::Square() {
  mapping = make_shared<SquareMapping>();

}
Square::Square (FLOAT left, FLOAT right, FLOAT top, FLOAT bottom) {
  this->top = top;
  this->left = left;
  this->right = right;
  this->bottom = bottom;
  mapping = make_shared<SquareMapping>();
}

Vector Square::getShapeNormal(IntersectHit &ih) {
  return normal;

}

void Square::shapeTestIntersect (QueueItemResults &results, Ray &ray, Ray &worldRay) {


  if (ray.start.z <0 && ray.direction.z < 0 ) {
    return;
  }

  if (ray.start.z >0 && ray.direction.z > 0 ) {
    return;
  }

  if (ray.direction.z == 0) {
    // no hit
    return;
  }


  FLOAT t = (0 - ray.start.z) / ray.direction.z;

  IntersectHit ih(this, t);
  ih.setShapeRay(ray);

  Point point = ih.getShapePoint();
  if ((point.x < left) || (point.y < top) ||
    (point.x> right) || (point.y > bottom)) {
      return;
    }

  if (!worldRay.isShadowRay) {
    ih.setWorldRay(worldRay);
    results.addResult(t, ih);
  }
  if (worldRay.isShadowRay && t < 1.0) {
    results.addResult(t, ih);
  }

}
