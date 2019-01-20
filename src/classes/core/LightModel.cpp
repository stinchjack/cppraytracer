#include "LightModel.hpp"
#include "Ray.hpp"
#include <cmath>


bool LightModel::processShadows  = true;

Colour LightModel::getColour(
    QueueItemResults &itemResults,
    int antialiasSamples,
    Scene *scene, int reflectionCount)
     {

  Colour c (0,0,0);

  if (scene->lights.size() > 0) {
    c += getDiffuse(itemResults, antialiasSamples, scene);
  }
  itemResults.begin()->second->scene = scene;
  c += reflection(itemResults.begin()->second, reflectionCount);

  return c;
}


FLOAT LightModel::shadowTest (
    Scene *scene,
    vector<Ray> &shadowRays) {


    if (!processShadows) {
      return 1.0;
    }

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

  //map<string, shared_ptr<Light>> &lights = scene->lights;
  IntersectHitPtr result = itemResults.begin()->second;

  //foreach light ...
//  for (auto lightIterator = lights.begin(); lightIterator != lights.end(); lightIterator++) {
//    shared_ptr<Light> light = lightIterator->second;

  int size = scene->tempLights.size();
  auto it = scene->tempLights.begin();

   //for (auto it = scene->tempLights.begin(); it!=scene->tempLights.end(); it++) {
   for (int i=0; i<size; i++) {
     shared_ptr<Light> light = *it;
    //PointLight p = *((shared_ptr<PointLight>)light);
    //cout<<light->colour.r<<endl;

    vector<Ray> shadowRays;
    light->getShadowRays(result, shadowRays);



    FLOAT shadowFactor =  LightModel::shadowTest(scene, shadowRays);

    if (shadowFactor == 0.0) {
      continue;
    }

    Vector averageLightDir(0,0,0);
    for (auto shadowRay = shadowRays.begin(); shadowRay != shadowRays.end(); shadowRay ++) {
      averageLightDir += shadowRay->direction;
    }

    averageLightDir *= 1.0/ shadowRays.size();

    Vector normal = result->getWorldNormal();

    normal.normalise();
    averageLightDir.normalise();


    FLOAT diffuseFactor = normal * averageLightDir;
    //if (result.getWorldRay().direction.normalised() * normal > 0) {
    if (result->getWorldRay().direction.normalised() * normal > 0) {
      diffuseFactor = 0 - diffuseFactor;
    }

    if (diffuseFactor > 0) {
      diffuse +=
        (result->getShape()->diffuse->getColour(result, result->getShape()->mapping))
        * diffuseFactor * shadowFactor;
    }
    it ++;
  }



  return diffuse;
}

Colour LightModel::reflection(IntersectHitPtr ih, int reflectionCount) {

  if (!ih->scene || reflectionCount < 1) {
    return Colour (0,0,0);
  }

  Colour specular = ih->getShape()->specular->getColour(ih, ih->getShape()->mapping);

  if (specular.r <=0 && specular.g <=0  && specular.b <= 0) {
    return Colour(0,0,0);
  }
  Vector normal = ih->getWorldNormal();
  if (ih->getWorldRay().direction.normalised() * normal > 0.0) {
    normal.reverse();
  }

  Point start = ih->getWorldPoint() + (normal * 0.0008);

  Vector dir = ih->getWorldRay().reflection(normal);

  Ray reflectedRay(start, dir);

  QueueItemResults queueItemResults;
  ViewQueueItem vqi(reflectedRay);
  ih->scene->testQueueItem(vqi , queueItemResults);
  if (queueItemResults.size() == 0) {
    return Colour (0,0,0);
  }
  Colour worldColour = LightModel::getColour(queueItemResults, 1, ih->scene, reflectionCount - 1);
  return worldColour * specular;
}
