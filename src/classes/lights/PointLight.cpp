#include "PointLight.hpp"


void PointLight::getShadowRays (IntersectHitPtr ih, vector<Ray> &shadowRays) {

  if (shadowRays.size() != 1) {
    shadowRays.resize(1);
  }

  Point testPoint = ih->getWorldPoint();

  Vector shadowDir (this->point - testPoint);

  Point shadowStart (testPoint);

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
  shadowRays[0] = shadowRay;

}



PointLight::PointLight (const Colour &c, const Point &p) {
  shadowTests = 1;
  colour = c;
  point = p;
}

 void PointLight::getTestPoints(Point testPoints[], IntersectHitPtr ih) {
   testPoints[0] = point;
 }
