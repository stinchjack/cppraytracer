#include "LightModel.hpp"
#include "Ray.hpp"
#include <cmath>

Colour LightModel::getColour(
    QueueItemResults &itemResults,
    int antialiasSamples,
    Scene *scene) {

  if (scene->lights.size() == 0) {
    return Colour(0,0,0);
  }

  //get the closest hit from the itemResults
  IntersectHit &result = itemResults.begin()->second;

  //Ray::calcPos method fills IntersectHit::hitPoint with calulation
  result.worldRay.calcPos(itemResults.begin()->first, result.hitPoint);



  return getDiffuse(itemResults, antialiasSamples, scene) / antialiasSamples;
}

FLOAT LightModel::shadowTest (
    Scene *scene,
    vector<Ray> &shadowRays) {

    int shadows = 0;
    int totalShadows = 0;
    for (auto shadowRay = shadowRays.begin();
      shadowRay != shadowRays.end(); shadowRay++) {

        totalShadows++;
        if (scene->shadowTest(*shadowRay)) {
          shadows++;
        }

    }
    return 1.0 - ((FLOAT)shadows/(FLOAT)totalShadows);
  };

Colour LightModel::getDiffuse (
    QueueItemResults &itemResults,
    int samples,
    Scene *scene) {
  Colour diffuse(0,0,0);

  map<string, shared_ptr<Light>> &lights = scene->lights;
  IntersectHit &result = itemResults.begin()->second;

  //foreach light ...
  for (auto lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++) {
    shared_ptr<Light> light = lightIterator->second;
    //PointLight p = *((shared_ptr<PointLight>)light);
    //cout<<light->colour.r<<endl;

    vector<Ray> shadowRays;
    light->getShadowRays(result, shadowRays);
    FLOAT shadowFactor =  LightModel::shadowTest(scene, shadowRays);

    Vector averageLightDir;
    for (auto shadowRay = shadowRays.begin(); shadowRay != shadowRays.end(); shadowRay ++) {
      averageLightDir += shadowRay->direction;
    }

    averageLightDir *= 1.0/ shadowRays.size();

    Vector shapeSpaceNormal = result.shape->getShapeNormal(result);
    Vector normal = result.shape->transformation.inverseTransform(shapeSpaceNormal);

    normal.normalise();
    averageLightDir.normalise();

    FLOAT diffuseFactor = abs (normal * averageLightDir);

    diffuse +=
      (result.shape->diffuse->getColour(result, result.shape->mapping))
      * diffuseFactor * shadowFactor;
  }



  return diffuse;
}
