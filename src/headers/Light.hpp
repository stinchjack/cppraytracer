#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Colour.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "IntersectResult.hpp"
#include <vector>
class Light {

public:
  Colour colour = Colour (1,1,1);

  unsigned int shadowTests;

  virtual void getShadowRays (IntersectHit &ih, vector<Ray> &shadowRays);

  virtual void getTestPoints(Point testPoints[], IntersectHit &ih) = 0;

};

class PointLight: public Light {

public:
    Point point;
    PointLight (const Colour &c, const Point &p);
    virtual void getTestPoints(Point testPoints[], IntersectHit &ih);
    virtual void getShadowRays (IntersectHit &ih, vector<Ray> &shadowRays);
};

#endif
