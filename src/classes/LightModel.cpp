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
  result.ray.calcPos(itemResults.begin()->first, result.hitPoint);

  map<string, shared_ptr<Light>> &lights = scene->lights;


  //foreach light ...
  for (auto lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++) {
    shared_ptr<Light> light = lights->second;

    vector<Ray> shadowRays;
    light->getShadowRays(result, shadowRays);

    Vector averageLightDir;
    for (auto shadowRay = shadowRays.begin(); shadowRay != shadowRays.end(); shadowRay ++) {
      averageLightDir += shadowRay.direction;
    }

    averageLightDir *= 1.0/ shadowRays.size();

    Vector shapeSpaceNormal = result.shape->getShapeNormal(ih);
    Vector normal = result.shape->transformation.inverseTransform(shapeSpaceNormal);

    normal.normalise();
    averageLightDir.normalise();

    FLOAT diffuseFactor = abs (normal * averageLightDir);

  }

  Colour diffuse = (result.shape->diffuse->getColour(result, result.shape->mapping)
    / (antialiasSamples)) * diffuseFactor;

  return diffuse;
}
