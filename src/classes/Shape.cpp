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

void Shape::testIntersect (QueueItemResults &results, Ray &ray) {
  Ray newRay(this->transformation.transform(ray.start), this->transformation.transform (ray.direction));
  shapeTestIntersect(results, newRay);

}

Ray Shape::transform (Ray &ray) {
  return Ray(this->transformation.transform(ray.start), this->transformation.transform (ray.direction));
}
