#include "Light.hpp"


/*
Light::getShadowRays is the general csae for shadow rays, allowing

for area-lights + soft sahdows
}
*/
void Light::getShadowRays (IntersectHit &ih, vector<Ray> &shadowRays) {
  if (shadowRays.size() != shadowTests) {
    shadowRays.resize(shadowTests);
  }

  Point testPoints[shadowTests];
  this->getTestPoints(testPoints, ih);
  //shadowRays.resize(shadowTest);

  //for (auto point = testPoints.begin(); point != testPoints.end(); point++) {
  for (unsigned int i=0; i< shadowTests; i++) {


    Vector shadowDir (
        testPoints[0][0] - ih.hitPoint[0],
        testPoints[0][1] - ih.hitPoint[1],
        testPoints[0][2] - ih.hitPoint[2]);

    Point shadowStart = {ih.hitPoint[0] + ((FLOAT).0001 * shadowDir.x),
      ih.hitPoint[1] + ((FLOAT).0001 * shadowDir.y),
      ih.hitPoint[2] + ((FLOAT).0001 * shadowDir.z)};

    Ray shadowRay (shadowStart, shadowDir);
    shadowRays[i] = shadowRay;
    i++;
  }
}


void PointLight::getShadowRays (IntersectHit &ih, vector<Ray> &shadowRays) {

  if (shadowRays.size() != 1) {
    shadowRays.resize(1);
  }

  Point testPoint {ih.hitPoint[0],  ih.hitPoint[1], ih.hitPoint[2]};

  Vector shadowDir (
      testPoint[0] - ih.hitPoint[0],
      testPoint[1] - ih.hitPoint[1],
      testPoint[2] - ih.hitPoint[2]);

  Point shadowStart = {ih.hitPoint[0] + ((FLOAT).0001 * shadowDir.x),
    ih.hitPoint[1] + ((FLOAT).0001 * shadowDir.y),
    ih.hitPoint[2] + ((FLOAT).0001 * shadowDir.z)};

  Ray shadowRay (shadowStart, shadowDir);
  shadowRays[0] = shadowRay;

}



PointLight::PointLight (const Colour &c, const Point &p) {
  shadowTests = 1;
  colour = c;
  point[0] = p[0];
  point[1] = p[1];
  point[2] = p[2];
}

 void PointLight::getTestPoints(Point testPoints[], IntersectHit &ih) {

   testPoints[0][0] = point[0];
   testPoints[0][1] = point[1];
   testPoints[0][2] = point[2];


 }
