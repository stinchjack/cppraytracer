#include "Light.hpp"


/*
Light::getShadowRays is the general csae for shadow rays, allowing

for area-lights + soft sahdows
}
*/
/*void Light::getShadowRays (IntersectHit &ih, vector<Ray> &shadowRays) {
  if (shadowRays.size() != shadowTests) {
    shadowRays.resize(shadowTests);
  }

  Point testPoints[shadowTests];
  this->getTestPoints(testPoints, ih);
  //shadowRays.resize(shadowTest);

  //for (auto point = testPoints.begin(); point != testPoints.end(); point++) {
  for (unsigned int i=0; i< shadowTests; i++) {


    Vector shadowDir (
        testPoints[0][0] - point[0],
        testPoints[0][1] - point[1],
        testPoints[0][2] - point[2]);

    Point shadowStart = {ih.hitPoint[0] + ((FLOAT).0001 * shadowDir.x),
      ih.hitPoint[1] + ((FLOAT).0001 * shadowDir.y),
      ih.hitPoint[2] + ((FLOAT).0001 * shadowDir.z)};

    Ray shadowRay (shadowStart, shadowDir);
    shadowRays[i] = shadowRay;
    i++;
  }
}*/


void PointLight::getShadowRays (IntersectHit &ih, vector<Ray> &shadowRays) {

  if (shadowRays.size() != 1) {
    shadowRays.resize(1);
  }

  Point testPoint = ih.getWorldPoint();

  Vector shadowDir (point - testPoint);

  Point shadowStart (testPoint);

  Vector normal = ih.getWorldNormal().normalised();

  if (shadowDir.normalised() * normal < 0.0) {
    shadowStart =  testPoint - (normal * 0.00001);
  }
  else {
    shadowStart =  testPoint + (normal * 0.00001);
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

 void PointLight::getTestPoints(Point testPoints[], IntersectHit &ih) {
   testPoints[0] = point;
 }
