#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "Light.hpp"
#include "Scene.hpp"

class PointLight: public Light {

public:
    Point point;
    PointLight (const Colour &c, const Point &p);
    virtual void getShadowInfo(
        Scene *scene,
        IntersectHitPtr ih,
        Vector &averageShadowDir,
        FLOAT &shadowFactor);
};

#endif
