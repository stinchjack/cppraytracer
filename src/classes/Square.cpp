#include  "Square.hpp"
#include <math.h>


SQAURE_PTR SquarePtr() {
  return std::make_shared<Sphere>();
}

SQAURE_PTR SquarePtr(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom) {
  return std::make_shared<Sphere> (left, right, top, bottom);
}



Square::Square ();
Square::Square (FLOAT left, FLOAT right, FLOAT top, FLOAT bottom) {
  this->top = top;
  this->left = left;
  this->right = right;
  this->bottom = bottom;
}

Vector Square::getShapeNormal(IntersectHit &ih) {
  return normal;

}

void Square::shapeTestIntersect (QueueItemResults &results, Ray &ray, Ray &worldRay) {

  if (ray.direction.z == 0) {
    // no hit
    return;
  }

  FLOAT t = (0 - ray.start.z) / ray.direction.z);

  IntersectHit ih(this, t);
  ih.setShapeRay(ray);

  Point point = ih.getShapePoint();
  if ((point.x < left) || (point.y < top) ||
    (point.x> right) || (point.y > bottom)) {
      return;
    }
  ih.setWorldRay(worldRay);
  results.addResult(t, ih);

}
