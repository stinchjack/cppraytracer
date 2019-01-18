#ifndef LIGHTMODEL_HPP
#define LIGHTMODEL_HPP

#include "IntersectHit.hpp"
#include "Colour.hpp"
#include "QueueItemResults.hpp"
#include "Scene.hpp"

using namespace std;

class LightModel {

private:
  static Colour getDiffuse(
    QueueItemResults &itemResults,
    int samples,
    Scene *scene);

  static Colour reflection(IntersectHitPtr ih, int reflectionCount);



public:

  static bool processShadows;

  static Colour getColour (
    QueueItemResults &itemResults,
    int samples,
    Scene *scene, int reflectionCount);

  static FLOAT shadowTest (
      Scene *scene,
      vector<Ray> &shadowRays);


};


#endif
