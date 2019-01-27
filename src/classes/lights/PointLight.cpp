#include "PointLight.hpp"


PointLight::PointLight (const Colour &c, const Point &p) {
  colour = c;
  point = p;
}


void PointLight::getShadowInfo(
    Scene *scene,
    IntersectHitPtr ih,
    Vector &averageShadowDir,
    FLOAT &shadowFactor) {

  Point testPoint = ih->getWorldPoint();

  Vector shadowDir (this->point - testPoint);

  Point shadowStart;

  Vector normal = ih->getWorldNormal();//.normalised();
  Vector eyedir = ih->getWorldRay().direction;//.normalised();

  if (eyedir * normal > 0.0) {
    shadowStart =  testPoint - (normal * 0.01);
  }
  else {
    shadowStart =  testPoint + (normal * 0.01);
  }

  Ray shadowRay (shadowStart, shadowDir);
  shadowRay.isShadowRay = true;

  if (scene->shadowTest(shadowRay)) {
    shadowFactor = 0;
  }
  else {
    shadowFactor = 1;
  }

  averageShadowDir = shadowDir;
}
