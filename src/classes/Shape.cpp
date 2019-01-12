#include "Shape.hpp"
#include "Texture.hpp"

Shape::Shape() {
  diffuse = make_shared<PlainTexture> (Colour (0.5, 0.5, 0.5));
  mapping = make_shared<NoMapping>();
}

/*

void Shape::setDiffuse (const shared_ptr<Texture> c) {
  diffuse = c;
}
void Shape::setSpecular (const shared_ptr<Texture> c) {
  specular = c;
}
void Shape::setTransparency (const shared_ptr<Texture> c) {
  transparency =c;

}*/

void Shape::testIntersect (QueueItemResults &results, Ray &worldRay) {
  //Point worldRayStart = {worldRay.start[0], worldRay.start[1], worldRay.start[2]};

//  Ray newRay(this->tr


Point start;
#ifdef EYE_TRANSFORM_SHORTCUT
if (worldRay.startIsEye && !hasTransformedEyePoint) {

    transformedEyePoint = this->transformation.transform(worldRay.start);
    start = transformedEyePoint;
    hasTransformedEyePoint = true;

}
else {
  start = this->transformation.transform(worldRay.start);
}
#else
  start = this->transformation.transform(worldRay.start);
#endif
Ray newRay(start, this->transformation.transform (worldRay.direction));

  newRay.isShadowRay = worldRay.isShadowRay;

  shapeTestIntersect(results, newRay, worldRay);

}

Ray Shape::transform (Ray &ray) {
  return Ray(this->transformation.transform(ray.start), this->transformation.transform (ray.direction));
}
