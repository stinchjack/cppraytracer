#include "Shape.hpp"
#include "Texture.hpp"

Shape::Shape() {
  diffuse = make_shared<PlainTexture> (Colour (0.5, 0.5, 0.5));
  specular = make_shared<PlainTexture> (Colour (0,0,0));
  transparency = make_shared<PlainTexture> (Colour (0,0,0));
  mapping = make_shared<NoMapping>();
}


void Shape::testIntersect (QueueItemResults &results, Ray &worldRay) {

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
