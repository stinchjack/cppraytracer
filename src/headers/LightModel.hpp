#ifndef LIGHTMODEL_HPP
#define LIGHTMODEL_HPP

#include "IntersectResult.hpp"
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


public:

  static bool processShadows;

  static Colour getColour (
    QueueItemResults &itemResults,
    int samples,
    Scene *scene);

  static FLOAT shadowTest (
      Scene *scene,
      vector<Ray> &shadowRays);


};


#endif
