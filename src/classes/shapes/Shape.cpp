#include "Shape.hpp"
#include "Texture.hpp"

Shape::Shape() {
  diffuse = make_shared<PlainTexture> (Colour (0.5, 0.5, 0.5));
  specular = make_shared<PlainTexture> (Colour (0,0,0));
  transparency = make_shared<PlainTexture> (Colour (0,0,0));
  mapping = make_shared<NoMapping>();
}


BoundingBoxPlanes Shape::getWorldBoundingPlanes() {
  if (!hasWorldPlanes) {
    worldPlanes =  box.getWorldPlanes(transformation);
    hasWorldPlanes = true;
  }
  return worldPlanes;
}

void Shape::testIntersect (QueueItemResults &results, Ray &worldRay) {


  if (!hasWorldPlanes) {getWorldBoundingPlanes();}
  if ((worldRay.start.x < worldPlanes.left && worldRay.direction.x < 0)
    || (worldRay.start.x > worldPlanes.right && worldRay.direction.x > 0)
    || (worldRay.start.y < worldPlanes.top && worldRay.direction.y < 0)
    || (worldRay.start.y > worldPlanes.bottom && worldRay.direction.y > 0)
    || (worldRay.start.z < worldPlanes.front && worldRay.direction.z < 0)
    || (worldRay.start.z > worldPlanes.back && worldRay.direction.z > 0)) {
    return;
  }


  Point start;

  if (worldRay.startIsEye && !hasTransformedEyePoint) {
      start = this->transformation.transform(worldRay.start);
      transformedEyePoint = start;
      hasTransformedEyePoint = true;

  }
  else if (worldRay.startIsEye && hasTransformedEyePoint) {
    start = transformedEyePoint;

  }
  else  {
      start = this->transformation.transform(worldRay.start);
  }



  Ray newRay(start, this->transformation.transform (worldRay.direction));
  newRay.isShadowRay = worldRay.isShadowRay;
  shapeTestIntersect(results, newRay, worldRay);


  //speed up for single thread only ...
  /*this->tempRay.start = start;
  this->tempRay.direction = this->transformation.transform (worldRay.direction);
  this->tempRay.isShadowRay = worldRay.isShadowRay;
  shapeTestIntersect(results, this->tempRay, worldRay);*/

}

Ray Shape::transform (Ray &ray) {
  return Ray(this->transformation.transform(ray.start), this->transformation.transform (ray.direction));
}

void Shape::setShift(const Point &p) {
  transformation.setShift (p);
}
void Shape::setRotate(const Vector &axis, FLOAT angle) {
  transformation.setRotate(axis, angle);
}
void Shape::setScale(FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ ) {
  transformation.setScale(scaleX, scaleY, scaleZ);
}
