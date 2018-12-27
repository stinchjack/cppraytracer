#ifndef LIGHTMODEL_HPP
#define LIGHTMODEL_HPP

#include "IntersectResult.hpp"
#include "Colour.hpp"
#include "QueueItemResults.hpp"
#include "Scene.hpp"

using namespace std;

class LightModel {

private:
  //static Colour calcDiffuse(IntersectHit &ih);
public:
  static Colour getColour (
    QueueItemResults &itemResults,
    int samples,
    Scene *scene);


};


#endif
