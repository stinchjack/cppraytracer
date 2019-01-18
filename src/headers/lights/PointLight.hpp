#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "Light.hpp"

class PointLight: public Light {

public:
    Point point;
    PointLight (const Colour &c, const Point &p);
    virtual void getTestPoints(Point testPoints[], IntersectHitPtr ih);
    virtual void getShadowRays (IntersectHitPtr ih, vector<Ray> &shadowRays);
};

#endif
