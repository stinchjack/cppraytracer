#include  "Square.hpp"
#include <math.h>




Square::Square() {
  mapping = make_shared<SquareMapping>();
  #ifdef EXPERIMENTAL
  box = BoundingBox(-1,1,0,-1,-.0001, .0001);
  #endif
}
Square::Square (FLOAT left, FLOAT right, FLOAT top, FLOAT bottom) {
  this->top = top;
  this->left = left;
  this->right = right;
  this->bottom = bottom;
  #ifdef EXPERIMENTAL
  box = BoundingBox(left, right, top, bottom,-.0001, .0001);
  #endif
  mapping = make_shared<SquareMapping>();
}

Vector Square::getShapeNormal(IntersectHit *ih) {
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





  Point point = ray.calcPos(t);

  if ((point.x < left) || (point.y < top) ||
    (point.x> right) || (point.y > bottom)) {
      return;
    }

  if (!worldRay.isShadowRay
    || (worldRay.isShadowRay && t < 1.0 && t>0)) {

      IHPtr hit = results.addResult (t, this);
      hit->setShapeRay(ray);
      hit->setWorldRay(worldRay);
  }


}
