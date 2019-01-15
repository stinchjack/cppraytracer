#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "Light.hpp"

class PointLight: public Light {

public:
    Point point;
    PointLight (const Colour &c, const Point &p);
    virtual void getTestPoints(Point testPoints[], IntersectHit &ih);
    virtual void getShadowRays (IntersectHit &ih, vector<Ray> &shadowRays);
};

#endif
