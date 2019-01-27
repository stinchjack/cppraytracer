#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Colour.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "IntersectHit.hpp"
#include <vector>
class Light {

public:
  Colour colour = Colour (1,1,1);

  unsigned int shadowTests;

  virtual void getShadowInfo(
      Scene *scene,
      IntersectHitPtr ih,
      Vector &averageShadowDir,
      FLOAT &shadowFactor) = 0;

};



#endif
