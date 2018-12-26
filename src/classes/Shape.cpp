#include "Shape.hpp"

void Shape::setDiffuse (const Colour &c) {
  diffuse = c;
}
void Shape::setSpecular (const Colour &c) {
  specular = c;
}
void Shape::setTransparency (const Colour &c) {
  transparency =c;

}

void Shape::testIntersect (QueueItemResults &results, Ray &ray) {
  Ray newRay(this->transformation.transform(ray.start), this->transformation.transform (ray.direction));
  shapeTestIntersect(results, newRay);

}

Ray Shape::transform (Ray &ray) {
  return Ray(this->transformation.transform(ray.start), this->transformation.transform (ray.direction));
}
