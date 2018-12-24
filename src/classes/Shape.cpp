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

void Shape::shapeTestIntersect (QueueItemResults &results, Ray &ray) {
  testInteresect(results, this->transform.transfor(ray));
}
    
